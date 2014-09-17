#include "maze_generator_kruskal.h"
#include <time.h>
#include <set>

struct edge
{
    void reset()
    {
        WspX1=0;
        WspY1=0;
        WspX2=0;
        WspY2=0;
        bActive=false;
    }
    int  WspX1;
    int  WspY1;
    int  WspX2;
    int  WspY2;
    bool bActive;
};

struct   Lokacja
{
    void reset()
    {
        Head=this;
        Tail=this;
        Next=NULL;
        Prev=NULL;
    }
    //
    unsigned int   uiSet;
    //
    unsigned int   ID;
    Lokacja   *Next,*Prev,*Head,*Tail;
};
//*m_vLocations

class maze_generator_kruskal_private
{
public:
	maze_generator_kruskal_private();
    unsigned int MakeID(unsigned int X, unsigned int Y);
    //resets location parameters before generation and assign starting ID values for set and locations
    void ResetGenLocation();
    //sets indices of locations on both sides of every edges
    void PrepareEdges();
    void JoinSets(unsigned int Wsp_A,unsigned int Wsp_B);

    void RemoveEdge(unsigned int index1,unsigned int index2);
    //transfer generation results from m_vLocations into m_MazeData
    void SetLocations();

    void PerformLocationReset();
    void AllocateLocationTable();
    void MakeNotPerfect();

    int                         size_x,size_y;
    unsigned int                edge_count;
    unsigned int                nodes_count;
    //maze                        maze_data;
    std::vector< edge >         edges;
    std::vector< Lokacja >      locations;
	std::shared_ptr<maze>       maze_data ;

};

maze_generator_kruskal_private::maze_generator_kruskal_private() :maze_data(new maze)
{

}
void maze_generator_kruskal_private::PerformLocationReset()
{
    //int index1,index2;
    for(int index1=0; index1<size_x; index1++)
        for(int index2=0; index2<size_y; index2++)
            maze_data->m_vvMapa[index1][index2].reset();
}
void maze_generator_kruskal_private::AllocateLocationTable()
{
	maze_data->size_x = size_x;
	maze_data->size_y = size_y;

    edge_count =  2*size_x*size_y-size_y-size_x ;
    nodes_count = size_x * size_y;

    locations.resize(nodes_count);
    edges.resize(edge_count);

    //przygotowujemy i alokujemy pamiec na tablice labiryntu
	maze_data->m_vvMapa.resize(size_x);
    for(int index=0; index<size_x; index++)
		maze_data->m_vvMapa[index].resize(size_y);
}
void maze_generator_kruskal_private::ResetGenLocation()
{
    unsigned int index=0;
    for(index=0; index<nodes_count; index++)
    {
        locations[index].reset();
        locations[index].uiSet=index+1;
        locations[index].ID=index+1;
    }
}
//////////////////////////////////////////////////////////////////////////
void maze_generator_kruskal_private::JoinSets(unsigned int Wsp_A, unsigned int Wsp_B)
{
    Lokacja *akt;
    //idziemy do pierwszego w zestawie A
    //idzie na koniec zestawu A
    akt=(locations[Wsp_A].Head)->Tail;
    //koniec zestawu A jako nastêpny wskazuje na poczatek zestawu B
    akt->Next=locations[Wsp_B].Head;
    do
    {
        akt=akt->Next;
        //zmien wskaznik na poczatek zestawu A
        akt->Head=locations[Wsp_A].Head;
        //ustaw taki sam kod zestawu
        akt->uiSet=(locations[Wsp_A].Head)->uiSet;
    }
    while((akt->Next)!=NULL);
    //poniewaz jestes na koncu zestawu B i koncu zestawu polaczonego
    //ustaw wskaznik w glowie zestawu polaczonego
    //na koniec polaczonego zestawu
    (locations[Wsp_A].Head)->Tail=akt;
}
void maze_generator_kruskal_private::PrepareEdges()
{
    unsigned int index=0,index1=0,index2=0;
    unsigned int X=size_x,Y=size_y;
    index=0;
    for(index1=0; index1<Y; index1++)
        for(index2=0; index2<X-1; index2++)
        {
            edges[index].WspX1=index2;
            edges[index].WspY1=index1;
            edges[index].WspX2=index2+1;
            edges[index].WspY2=index1;
            edges[index].bActive=true;
            index++;
        }

    for(index1=0; index1<Y-1; index1++)
        for(index2=0; index2<X; index2++)
        {
            edges[index].WspX1=index2;
            edges[index].WspY1=index1;
            edges[index].WspX2=index2;
            edges[index].WspY2=index1+1;
            edges[index].bActive=true;
            index++;
        }
}
void maze_generator_kruskal_private::RemoveEdge(unsigned int index1, unsigned int index2)
{
    unsigned int index=0,Count=0;
    unsigned int X1=0,X2=0,Y1=0,Y2=0;
    edge	temp;
    X1=index1%size_x;
    Y1=index1/size_x;
    X2=index2%size_x;
    Y2=index2/size_x;
    Count=edges.size();
    for(index=0; index<Count; index++)
    {
        temp = edges[index];
        if  (( temp.WspX1 == X1 && temp.WspY1 == Y1
                && temp.WspX2 == X2 && temp.WspY2 == Y2 ) ||
                ( temp.WspX2 == X1 && temp.WspY2 == Y1
                  && temp.WspX1 == X2 && temp.WspY1 == Y2 ) )
        {
            edges[index].bActive=false;
            return;
        }
    }
}
void maze_generator_kruskal_private::SetLocations()
{
    unsigned int index=0;
    for(index=0; index<edge_count; index++)
        if (edges[index].bActive==true)
        {
            if (edges[index].WspY1==edges[index].WspY2)
            {
				maze_data->m_vvMapa[edges[index].WspX1][edges[index].WspY1].set_wall(EAST_DIR);
				maze_data->m_vvMapa[edges[index].WspX2][edges[index].WspY2].set_wall(WEST_DIR);
            }
            else
            {
				maze_data->m_vvMapa[edges[index].WspX1][edges[index].WspY1].set_wall(SOUTH_DIR);
				maze_data->m_vvMapa[edges[index].WspX2][edges[index].WspY2].set_wall(NORTH_DIR);
            }
        }
}
unsigned int maze_generator_kruskal_private::MakeID(unsigned int X, unsigned int Y)
{
    return (X+Y*X);
}
void maze_generator_kruskal_private::MakeNotPerfect()
{
    /*int X, Y;
    unsigned int X1, Y1;
    unsigned int count,index,index1;
    unsigned int indir,outdir;
    location * pLoc;
    location * pLoc1;
    bool dirs[4];

    bool up,down,right,left;
    srand( (unsigned)time( NULL ) );

    for(X=1; X<=size_x; X++)
        for(Y=1; Y<=size_y; Y++)
        {
			boost::optional<location> location_ = maze_data.get_location(X,Y,up,down,right,left);
            dirs[0] = up ?		true : false;
            dirs[1] = down ?	true : false;
            dirs[2] = right ?	true : false;
            dirs[3] = left ?	true : false;

            for(count=0,index=0; index<4 ; index++)
                if (dirs[index])	count++;
            //skoro to œlepy zau³ek - usuñ dowoln¹ œcianê
            if (count==3)
            {
                X1=X;
                Y1=Y;

                for(indir=0; indir<4; indir++)
                    if (!dirs[indir])	break;
                if (indir>=4) indir=255;
                //usun œciany bêd¹ce granicami labiryntu
                if (X == 1 && left)		dirs[3]=false;
                else if (X == size_x && right)				dirs[2]=false;
                if (Y == 1 && up)		dirs[0]=false;
                else if (Y == size_y && down)				dirs[1]=false;

                for(count=0,index=0; index<4 ; index++)
                    if (dirs[index])	count++;

                //wybierz kierunek
                if (count==1)
                {
                    for(count=0; count<4 ; count++)
                        if (dirs[count])	break;
                }
                else
                {
                    //najpierw sprawdz czy mozna usun¹æ œcianê naprzeci wejscia
                    if (indir!=255)
                    {
                        switch(indir)
                        {
                        case 0:
                            if (dirs[1]) count=1;
                            break;
                        case 1:
                            if (dirs[0]) count=0;
                            break;
                        case 2:
                            if (dirs[3]) count=3;
                            break;
                        case 3:
                            if (dirs[2]) count=2;
                            break;
                        default:
                            outdir=255;
                        }
                    }
                    else
                        //					if (outdir==255)
                    {
                        index = 1 + rand()%count;
                        count=0;
                        for(index1=0; index1<4 ; index1++)
                        {
                            if (dirs[index1])	count++;
                            if (count==index)	break;
                        }
                        count=index1;
                    }
                    //					else
                    //						count=outdir;
                }
                switch(count)
                {
                case 0:
                    Y1=Y-1;
                    break;
                case 1:
                    Y1=Y+1;
                    break;
                case 2:
                    X1=X+1;
                    break;
                case 3:
                    X1=X-1;
                    break;
                }

                pLoc = &maze_data.m_vvMapa[X-1][Y-1];
                pLoc1 = &maze_data.m_vvMapa[X1-1][Y1-1];
                switch(count)
                {
                case 0:	//UP
                    pLoc->up=false;
                    pLoc1->down=false;
                    break;
                case 1:	//DOWN
                    pLoc->down=false;
                    pLoc1->up=false;
                    break;
                case 2:	//RIGHT
                    pLoc->right=false;
                    pLoc1->left=false;
                    break;
                case 3:	//LEFT
                    pLoc->left=false;
                    pLoc1->right=false;
                    break;
                }
            }
        }*/
}
//////////////////////////////////////////////////////////////////////////
maze_generator_kruskal::maze_generator_kruskal() : pimpl(new maze_generator_kruskal_private){}
maze_generator_kruskal::~maze_generator_kruskal()
{

}

std::shared_ptr<maze_interface> maze_generator_kruskal::generate_maze(const maze_settings & xMazeSettings)
{
    /*pimpl->PerformLocationReset();
    pimpl->size_x=xMazeSettings.size_x;
    pimpl->size_y=xMazeSettings.size_y;
    pimpl->AllocateLocationTable();

	unsigned int index = 0, index1 = 0;
	unsigned int Wsp_A = 0, Wsp_B = 0;
	unsigned int IleLaczen = 0;

	pimpl->ResetGenLocation();
	//tworzymy tablice z wszystkimi scianami wystepujacymi
	PrepareEdges();
	maze_data.SetMazeEdges();
	//losuje rozmieszczenie krawedzi
	srand((unsigned)time(NULL));
	edge temp;
	for (index = 0; index < edge_count; index++)
	{
		index1 = rand() % (edge_count - 1);
		temp = edges[index];
		edges[index] = edges[index1];
		edges[index1] = temp;
	}

	//generowanie labiryntu testujemy poszczególne krawedzie
	for (index = 0; index < edge_count; index++)
	{
		//obliczamy wspolrzedna liniow¹ dla lokacji po obu stronach krawedzi
		Wsp_A = edges[index].WspX1 + edges[index].WspY1*size_x;
		Wsp_B = edges[index].WspX2 + edges[index].WspY2*size_x;
		//ustalamy wska¿nik na lokacje bazowa identyfikujaca dany uiSet

		//jeœli wska¿niki na globalny NrZestawy wskazuj¹ na ró¿ne zestawy
		//to usuñ krawe¿
		if ((locations[Wsp_A].uiSet) != (locations[Wsp_B].uiSet))
		{
			JoinSets(Wsp_A, Wsp_B);
			edges[index].bActive = false;
			IleLaczen++;
		}
	}
	SetLocations();*/

	return pimpl->maze_data;
}
