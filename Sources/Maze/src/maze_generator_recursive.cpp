#include "maze_generator_recursive.h"
#include "maze.h"
#include <set>
#include <stack>
#include <Tools/loggers.h>
#include <time.h>

class maze_generator_recursive_private
{
public:
	maze_generator_recursive_private();
	void generate_maze();
	void fill_unvisited_set();
	unsigned int make_id(unsigned int X, unsigned int Y);
	boost::optional<unsigned int> get_neighbour_cell(unsigned int current_cell);
	void allocate_locations_table();
	void reset_locations();
	void join_cells(unsigned int current_cell, unsigned int neighbour_cell);
public:
	unsigned int                size_x, size_y;
	//unsigned int                locations_id_mask;
	//std::vector<unsigned int>	edges_sets;
	//location_sets_type          locations_sets;
	std::shared_ptr<maze>     maze_data;
	std::set<unsigned int>  unvisited_cells;
};

maze_generator_recursive_private::maze_generator_recursive_private() : size_x(0), size_y(0), maze_data(new maze){}

void maze_generator_recursive_private::reset_locations()
{
	for (unsigned int index1 = 0; index1<size_x; index1++)
		for (unsigned int index2 = 0; index2<size_y; index2++)
            maze_data->m_vvMapa[index1][index2].reset();
}
void maze_generator_recursive_private::allocate_locations_table()
{
	maze_data->size_x = size_x;
	maze_data->size_y = size_y;

	unsigned int edge_count = 2 * size_x*size_y - size_y - size_x;
	//locations_id_mask = get_bits_size(edge_count);

	maze_data->m_vvMapa.resize(size_x);
	for (unsigned int index = 0; index<size_x; index++)
		maze_data->m_vvMapa[index].resize(size_y);
	reset_locations();
	//locations_sets.clear();
	//for (unsigned int index = 0; index < size_x * size_y; index++)
		//locations_sets[index] = index;
}
unsigned int maze_generator_recursive_private::make_id(unsigned int X, unsigned int Y)
{
    return (X+Y*size_x);
}
void maze_generator_recursive_private::fill_unvisited_set()
{
	unvisited_cells.clear();
	for(unsigned int x=0;x<size_x;x++)
		for(unsigned int y=0;y<size_y;y++)
			unvisited_cells.insert(make_id(x,y));

}
boost::optional<unsigned int> maze_generator_recursive_private::get_neighbour_cell(unsigned int current_cell)
{
	unsigned int x = current_cell % size_x;
	unsigned int y = current_cell / size_y;
	unsigned int neighbour_cell;
	//get_unvisited_neighboor_cell(current_cell);
	std::vector<unsigned int> neighbours;
	neighbour_cell = make_id(x-1,y);
	if (x>0 && unvisited_cells.count(neighbour_cell))
		neighbours.push_back(neighbour_cell);
	neighbour_cell = make_id(x,y-1);
	if (y>0 && unvisited_cells.count(neighbour_cell))
		neighbours.push_back(neighbour_cell);
	neighbour_cell = make_id(x+1,y);
	if (x<size_x && unvisited_cells.count(neighbour_cell))
		neighbours.push_back(neighbour_cell);
	neighbour_cell = make_id(x,y+1);
	if (y<size_y && unvisited_cells.count(neighbour_cell))
		neighbours.push_back(neighbour_cell);
	boost::optional<unsigned int> return_val;
	if (neighbours.size())
	{
		int index = rand() %neighbours.size();
		return_val = neighbours[index];
	}
	return return_val;
}
void maze_generator_recursive_private::generate_maze()
{
	//printLog(eDebug,eDebugLogLevel, "IN: Start generate_maze");
    srand( (unsigned)time( NULL ) );
    fill_unvisited_set();

	unsigned int current_cell = rand()%make_id(size_x-1,size_y-1)-1;
	std::stack<unsigned int> stack_;
	unvisited_cells.erase(current_cell);
	//take initial cell
	while(unvisited_cells.size())
	{
		unsigned int current_x = current_cell % size_x;
		unsigned int current_y = current_cell / size_y;
		boost::optional<unsigned int> neighbour_cell;
		boost::optional<location> curr_loc = maze_data->get_location(current_x, current_y);
		if ((neighbour_cell = get_neighbour_cell(current_cell)))
		{
			stack_.push(current_cell);
			join_cells(current_cell, neighbour_cell.get());
			current_cell = neighbour_cell.get();
			unvisited_cells.erase(current_cell);
		}
		else if (stack_.size())
		{
			current_cell = stack_.top();
			stack_.pop();
		}
		else
		{
			std::set<unsigned int>::iterator it = unvisited_cells.begin();
			unsigned int index = rand()%unvisited_cells.size()-1;
			std::advance(it, index);
			current_cell = *it;
			unvisited_cells.erase(current_cell);
		}
	}
	//printLog(eDebug,eDebugLogLevel, "IN: End generate_maze");
}
void maze_generator_recursive_private::join_cells(unsigned int current_cell, unsigned int neighbour_cell)
{
	unsigned int current_x = current_cell % size_x;
	unsigned int current_y = current_cell / size_y;
	unsigned int neighbour_x = neighbour_cell % size_x;
	unsigned int neighbour_y = neighbour_cell / size_y;
	location & loc = maze_data->get_xlocation(neighbour_x, neighbour_y);
	location & curr_loc = maze_data->get_xlocation(current_x, current_y);

	if (current_x == neighbour_x)
	{
		if (current_y > neighbour_y)
		{
			curr_loc.set_passage(NORTH_DIR);
			loc.set_passage(SOUTH_DIR);
		}
		else
		{
			curr_loc.set_passage(SOUTH_DIR);
			loc.set_passage(NORTH_DIR);
		}
	} else {
		if (current_x > neighbour_x)
		{
			curr_loc.set_passage(WEST_DIR);
			loc.set_passage(EAST_DIR);
		}
		else
		{
			curr_loc.set_passage(EAST_DIR);
			loc.set_passage(WEST_DIR);
		}
	}

}

////////////////////////////////////////////////////////////////////////////////
maze_generator_recursive::maze_generator_recursive():pimpl(new maze_generator_recursive_private()){}
maze_generator_recursive::~maze_generator_recursive(){}
std::shared_ptr<maze_interface> maze_generator_recursive::generate_maze(const maze_settings & settings)
{
	///printLog(eDebug,eDebugLogLevel, "generate_maze");
	pimpl->size_x = settings.size_x;
	pimpl->size_y = settings.size_y;
	pimpl->allocate_locations_table();
	pimpl->maze_data->preset_maze_edges();
	pimpl->generate_maze();
	return pimpl->maze_data;
}

/*
#include <Maze/maze_generator.h>
#include <Maze/maze_generator_factory.h>
#include <time.h>
#include <QtCore/QStack>
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

class CMazeGeneratorPrivate
{
public:
    void GenerateMaze_Kruskal();
    void GenerateMaze_Recursive();
    void GenerateMaze_Prim();
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
    maze                        maze_data;
    std::vector< edge >         edges;
    std::vector< Lokacja >      locations;
};

void CMazeGeneratorPrivate::PerformLocationReset()
{
    //int index1,index2;
    for(int index1=0; index1<size_x; index1++)
        for(int index2=0; index2<size_y; index2++)
            maze_data.m_vvMapa[index1][index2].reset();
}
void CMazeGeneratorPrivate::AllocateLocationTable()
{
    maze_data.size_x = size_x;
    maze_data.size_y = size_y;

    edge_count =  2*size_x*size_y-size_y-size_x ;
    nodes_count = size_x * size_y;

    locations.resize(nodes_count);
    edges.resize(edge_count);

    //przygotowujemy i alokujemy pamiec na tablice labiryntu
    maze_data.m_vvMapa.resize(size_x);
    for(int index=0; index<size_x; index++)
        maze_data.m_vvMapa[index].resize(size_y);
}
void CMazeGeneratorPrivate::ResetGenLocation()
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
void CMazeGeneratorPrivate::GenerateMaze_Kruskal()
{

    unsigned int index=0,index1=0;
    unsigned int Wsp_A=0,Wsp_B=0;
    unsigned int IleLaczen=0;

    ResetGenLocation();
    //tworzymy tablice z wszystkimi scianami wystepujacymi
    PrepareEdges();
    maze_data.SetMazeEdges();
    //losuje rozmieszczenie krawedzi
    srand( (unsigned)time( NULL ) );
    edge temp;
    for(index=0; index<edge_count; index++)
    {
        index1=rand()%(edge_count-1);
        temp=edges[index];
        edges[index]=edges[index1];
        edges[index1]  =temp;
    }

    //generowanie labiryntu testujemy poszczeg�lne krawedzie
    for(index=0; index<edge_count; index++)
    {
        //obliczamy wspolrzedna liniow� dla lokacji po obu stronach krawedzi
        Wsp_A=edges[index].WspX1+edges[index].WspY1*size_x;
        Wsp_B=edges[index].WspX2+edges[index].WspY2*size_x;
        //ustalamy wska�nik na lokacje bazowa identyfikujaca dany uiSet

        //je�li wska�niki na globalny NrZestawy wskazuj� na r�ne zestawy
        //to usu� krawe�
        if ( (locations[Wsp_A].uiSet) != (locations[Wsp_B].uiSet))
        {
            JoinSets(Wsp_A,Wsp_B);
            edges[index].bActive=false;
            IleLaczen++;
        }
    }
    SetLocations();
}
void CMazeGeneratorPrivate::GenerateMaze_Recursive()
{
    int index=0,index1=0,index2=0;
    //	unsigned int EdgeCount =  2*X*Y-Y-X ;
    //	unsigned int NodesCount = X * Y;
    unsigned int Count=0;
    int 			iNeighbour;

    QStack<int>	stack;

    ResetGenLocation();
    maze_data.SetMazeEdges();
    PrepareEdges();
    //przygotowujemy i alokujemy pamiec na tablice labiryntu

    srand( (unsigned)time( NULL ) );
    index = rand()%(nodes_count-1);
    stack.push(index);
    do
    {
        iNeighbour=0;
        //zdejmujemy wsp liniowa lokacji
        Count = stack.size();
        index = stack.pop();
        Count = stack.size();
        //sprawdzamy s�siad�w czy jest do nich dojscie
        //wybieramy losowo jeden z kierunkow
        index1 = rand()%4;
        do
        {
            switch(index1)
            {
            case 0:	//polnoc
            {
                //sprawdzamy czy wsp nie wskazuje na lokacje w pierwszym rzedzie
                if ((index/size_x)<1)
                {
                    iNeighbour++;
                    break;
                }
                index2=index-size_x;
                if ( (locations[index].uiSet) != (locations[index2].uiSet))
                {
                    JoinSets(index,index2);
                    RemoveEdge(index,index2);
                    stack.push(index);
                    stack.push(index2);
                    iNeighbour=0;
                }
                else
                    iNeighbour++;
                break;
            }
            case 1:	//wschod
            {
                if ((index%size_x)==size_x-1)
                {
                    iNeighbour++;
                    break;
                }
                index2=index+1;
                if ( (locations[index].uiSet) != (locations[index2].uiSet))
                {
                    JoinSets(index,index2);
                    RemoveEdge(index,index2);
                    stack.push(index);
                    stack.push(index2);
                    iNeighbour=0;
                }
                else
                    iNeighbour++;
                break;
            }
            case 2:	//poludnie
            {
                if ((index/size_x)>=size_y-1)
                {
                    iNeighbour++;
                    break;
                }
                index2=index+size_x;
                if ( (locations[index].uiSet) != (locations[index2].uiSet))
                {
                    JoinSets(index,index2);
                    RemoveEdge(index,index2);
                    stack.push(index);
                    stack.push(index2);
                    iNeighbour=0;
                }
                else
                    iNeighbour++;
                break;
            }
            case 3:	//zachod
            {
                if ((index%size_x)==0)
                {
                    iNeighbour++;
                    break;
                }
                index2=index-1;
                if ( (locations[index].uiSet) != (locations[index2].uiSet))
                {
                    JoinSets(index,index2);
                    RemoveEdge(index,index2);
                    stack.push(index);
                    stack.push(index2);
                    iNeighbour=0;
                }
                else
                    iNeighbour++;
                break;
            }
            break;
            }
            if (iNeighbour==4 || iNeighbour==0) break;
            if (index1==3)
                index1=0;
            else index1++;
        }
        while(1);
    }
    while(!stack.isEmpty());
    SetLocations();
}
void CMazeGeneratorPrivate::GenerateMaze_Prim()
{
    int index=0,index1=0,index2=0,prev_index=0;
    std::set<unsigned int>	sInCells,sFrontierCells,sNeighbour;

    // 	for(index1=0;index1<Maze_X;index1++)
    // 		for(index2=0;index2<Maze_Y;index2++)
    // 			mapa[index1][index2].Reset();

    QStack<int>	stack;

    ResetGenLocation();
    maze_data.SetMazeEdges();
    PrepareEdges();
    //przygotowujemy i alokujemy pamiec na tablice labiryntu
    srand( (unsigned)time( NULL ) );
    index = rand()%(nodes_count-1);
    prev_index=index;
    sFrontierCells.insert(index);

    do
    {
        //wybieramy losowo jeden element z listy komorek sasiadujacych
        index1 = rand()%sFrontierCells.size();
        index2=0;
        foreach(index,sFrontierCells)
        {
            if ( index2 == index1 )
                break;
            else
                index2++;
        }
        sFrontierCells.erase(index);
        sInCells.insert(index);
        sNeighbour.clear();

        if ((index/size_x)>=1 && !sFrontierCells.count(index-size_x) && !sInCells.count(index-size_x))	//polnoc
            sFrontierCells.insert(index-size_x);
        if ((index%size_x)>0 &&	!sFrontierCells.count(index-1) && !sInCells.count(index-1))	//zachod
            sFrontierCells.insert(index-1);
        if ((index/size_x)<size_y-1 &&!sFrontierCells.count(index+size_x) && !sInCells.count(index+size_x))	//poludnie
            sFrontierCells.insert(index+size_x);
        if ((index%size_x)!=size_x-1 && !sFrontierCells.count(index+1) && !sInCells.count(index+1))	//wschod
            sFrontierCells.insert(index+1);

        if ((index/size_x)>=1 && sInCells.count(index-size_x))	//polnoc
            sNeighbour.insert(index-size_x);
        if ((index%size_x)>0 && sInCells.count(index-1))	//zachod
            sNeighbour.insert(index-1);
        if ((index/size_x)<size_y-1 && sInCells.count(index+size_x))	//poludnie
            sNeighbour.insert(index+size_x);
        if ((index%size_x)!=size_x-1 && sInCells.count(index+1))	//wschod
            sNeighbour.insert(index+1);

        if (sNeighbour.size()>0)
        {
            index1 = rand()%sNeighbour.size();
            index2=0;
            foreach(prev_index,sNeighbour)
            {
                if ( index2 == index1 )
                    break;
                else
                    index2++;
            }
        }
        else prev_index = index;
        if ( prev_index != index && locations[index].uiSet != locations[prev_index].uiSet)
        {
            JoinSets(index,prev_index);
            RemoveEdge(index,prev_index);
        }
    }
    while(!sFrontierCells.empty());
    sFrontierCells.clear();
    sInCells.clear();
    sNeighbour.clear();
    SetLocations();
}
void CMazeGeneratorPrivate::JoinSets(unsigned int Wsp_A,unsigned int Wsp_B)
{
    Lokacja *akt;
    //idziemy do pierwszego w zestawie A
    //idzie na koniec zestawu A
    akt=(locations[Wsp_A].Head)->Tail;
    //koniec zestawu A jako nast�pny wskazuje na poczatek zestawu B
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

void CMazeGeneratorPrivate::PrepareEdges()
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

void CMazeGeneratorPrivate::RemoveEdge(unsigned int index1,unsigned int index2)
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

void CMazeGeneratorPrivate::SetLocations()
{
    unsigned int index=0;
    for(index=0; index<edge_count; index++)
        if (edges[index].bActive==true)
        {
            if (edges[index].WspY1==edges[index].WspY2)
            {
                maze_data.m_vvMapa[edges[index].WspX1][edges[index].WspY1].right=true;
                maze_data.m_vvMapa[edges[index].WspX2][edges[index].WspY2].left=true;
            }
            else
            {
                maze_data.m_vvMapa[edges[index].WspX1][edges[index].WspY1].down=true;
                maze_data.m_vvMapa[edges[index].WspX2][edges[index].WspY2].up=true;
            }
        }
}
//CLocation & CMazeGenerator::getLocation(unsigned int X,unsigned int Y)
//{
//	return mapa[--X][--Y];
//}
unsigned int CMazeGeneratorPrivate::MakeID(unsigned int X, unsigned int Y)
{
    return (X+Y*X);
}
void CMazeGeneratorPrivate::MakeNotPerfect()
{
    int X, Y;
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
            maze_data.get_location(X,Y,up,down,right,left);
            dirs[0] = up ?		true : false;
            dirs[1] = down ?	true : false;
            dirs[2] = right ?	true : false;
            dirs[3] = left ?	true : false;

            for(count=0,index=0; index<4 ; index++)
                if (dirs[index])	count++;
            //skoro to �lepy zau�ek - usu� dowoln� �cian�
            if (count==3)
            {
                X1=X;
                Y1=Y;

                for(indir=0; indir<4; indir++)
                    if (!dirs[indir])	break;
                if (indir>=4) indir=255;
                //usun �ciany b�d�ce granicami labiryntu
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
                    //najpierw sprawdz czy mozna usun�� �cian� naprzeci wejscia
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
        }
}
//////////////////////////////////////////////////////////////////////////
const maze & maze_generator::generate_maze(unsigned int MaxX, unsigned int MaxY, EMazeTypes eMazeType)
{
    maze_settings xMazeSettings;
    xMazeSettings.size_x=MaxX;
    xMazeSettings.size_y=MaxY;
    xMazeSettings.mazeType=eMazeType;
    xMazeSettings.bMazePerfect=true;
	generate_maze(xMazeSettings);
	pimpl->maze_data.SetMazeEdges();
    return pimpl->maze_data;
}
const maze & maze_generator::generate_maze(const maze_settings & xMazeSettings)
{
    pimpl->PerformLocationReset();
    pimpl->size_x=xMazeSettings.size_x;
    pimpl->size_y=xMazeSettings.size_y;
    pimpl->AllocateLocationTable();

	maze_generator_factory

    switch (xMazeSettings.mazeType)
    {
    case E_MT_KRUSKAL:
        pimpl->GenerateMaze_Kruskal();
        break;
    case E_MT_PRIM:
        pimpl->GenerateMaze_Prim();
        break;
    case E_MT_RECURSIVE:
        pimpl->GenerateMaze_Recursive();
        break;
    default:
        break;
    }
    return pimpl->maze_data;
}
*/
