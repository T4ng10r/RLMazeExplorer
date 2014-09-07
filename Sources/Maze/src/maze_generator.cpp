#include "maze_generator.h"
#include <time.h>
#include <QtCore/QStack>
#include <set>

struct Krawedz
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

    int							iSizeX,iSizeY;
    unsigned int				m_EdgeCount;
    unsigned int				m_NodesCount;
    maze						m_MazeData;
    std::vector< Krawedz >		m_vEdges;
    std::vector< Lokacja >		m_vLocations;
};

void CMazeGeneratorPrivate::PerformLocationReset()
{
    //int index1,index2;
    for(int index1=0; index1<iSizeX; index1++)
        for(int index2=0; index2<iSizeY; index2++)
            m_MazeData.m_vvMapa[index1][index2].reset();
}
void CMazeGeneratorPrivate::AllocateLocationTable()
{
    m_MazeData.size_x = iSizeX;
    m_MazeData.size_y = iSizeY;

    m_EdgeCount =  2*iSizeX*iSizeY-iSizeY-iSizeX ;
    m_NodesCount = iSizeX * iSizeY;

    m_vLocations.resize(m_NodesCount);
    m_vEdges.resize(m_EdgeCount);

    //przygotowujemy i alokujemy pamiec na tablice labiryntu
    m_MazeData.m_vvMapa.resize(iSizeX);
    for(int index=0; index<iSizeX; index++)
        m_MazeData.m_vvMapa[index].resize(iSizeY);
}
void CMazeGeneratorPrivate::ResetGenLocation()
{
    unsigned int index=0;
    for(index=0; index<m_NodesCount; index++)
    {
        m_vLocations[index].reset();
        m_vLocations[index].uiSet=index+1;
        m_vLocations[index].ID=index+1;
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
    m_MazeData.SetMazeEdges();
    //losuje rozmieszczenie krawedzi
    srand( (unsigned)time( NULL ) );
    Krawedz temp;
    for(index=0; index<m_EdgeCount; index++)
    {
        index1=rand()%(m_EdgeCount-1);
        temp=m_vEdges[index];
        m_vEdges[index]=m_vEdges[index1];
        m_vEdges[index1]  =temp;
    }

    //generowanie labiryntu testujemy poszczególne krawedzie
    for(index=0; index<m_EdgeCount; index++)
    {
        //obliczamy wspolrzedna liniow¹ dla lokacji po obu stronach krawedzi
        Wsp_A=m_vEdges[index].WspX1+m_vEdges[index].WspY1*iSizeX;
        Wsp_B=m_vEdges[index].WspX2+m_vEdges[index].WspY2*iSizeX;
        //ustalamy wska¿nik na lokacje bazowa identyfikujaca dany uiSet

        //jeœli wska¿niki na globalny NrZestawy wskazuj¹ na ró¿ne zestawy
        //to usuñ krawe¿
        if ( (m_vLocations[Wsp_A].uiSet) != (m_vLocations[Wsp_B].uiSet))
        {
            JoinSets(Wsp_A,Wsp_B);
            m_vEdges[index].bActive=false;
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
    m_MazeData.SetMazeEdges();
    PrepareEdges();
    //przygotowujemy i alokujemy pamiec na tablice labiryntu

    srand( (unsigned)time( NULL ) );
    index = rand()%(m_NodesCount-1);
    stack.push(index);
    do
    {
        iNeighbour=0;
        //zdejmujemy wsp liniowa lokacji
        Count = stack.size();
        index = stack.pop();
        Count = stack.size();
        //sprawdzamy s¹siadów czy jest do nich dojscie
        //wybieramy losowo jeden z kierunkow
        index1 = rand()%4;
        do
        {
            switch(index1)
            {
            case 0:	//polnoc
            {
                //sprawdzamy czy wsp nie wskazuje na lokacje w pierwszym rzedzie
                if ((index/iSizeX)<1)
                {
                    iNeighbour++;
                    break;
                }
                index2=index-iSizeX;
                if ( (m_vLocations[index].uiSet) != (m_vLocations[index2].uiSet))
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
                if ((index%iSizeX)==iSizeX-1)
                {
                    iNeighbour++;
                    break;
                }
                index2=index+1;
                if ( (m_vLocations[index].uiSet) != (m_vLocations[index2].uiSet))
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
                if ((index/iSizeX)>=iSizeY-1)
                {
                    iNeighbour++;
                    break;
                }
                index2=index+iSizeX;
                if ( (m_vLocations[index].uiSet) != (m_vLocations[index2].uiSet))
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
                if ((index%iSizeX)==0)
                {
                    iNeighbour++;
                    break;
                }
                index2=index-1;
                if ( (m_vLocations[index].uiSet) != (m_vLocations[index2].uiSet))
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
    m_MazeData.SetMazeEdges();
    PrepareEdges();
    //przygotowujemy i alokujemy pamiec na tablice labiryntu
    srand( (unsigned)time( NULL ) );
    index = rand()%(m_NodesCount-1);
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

        if ((index/iSizeX)>=1 && !sFrontierCells.count(index-iSizeX) && !sInCells.count(index-iSizeX))	//polnoc
            sFrontierCells.insert(index-iSizeX);
        if ((index%iSizeX)>0 &&	!sFrontierCells.count(index-1) && !sInCells.count(index-1))	//zachod
            sFrontierCells.insert(index-1);
        if ((index/iSizeX)<iSizeY-1 &&!sFrontierCells.count(index+iSizeX) && !sInCells.count(index+iSizeX))	//poludnie
            sFrontierCells.insert(index+iSizeX);
        if ((index%iSizeX)!=iSizeX-1 && !sFrontierCells.count(index+1) && !sInCells.count(index+1))	//wschod
            sFrontierCells.insert(index+1);

        if ((index/iSizeX)>=1 && sInCells.count(index-iSizeX))	//polnoc
            sNeighbour.insert(index-iSizeX);
        if ((index%iSizeX)>0 && sInCells.count(index-1))	//zachod
            sNeighbour.insert(index-1);
        if ((index/iSizeX)<iSizeY-1 && sInCells.count(index+iSizeX))	//poludnie
            sNeighbour.insert(index+iSizeX);
        if ((index%iSizeX)!=iSizeX-1 && sInCells.count(index+1))	//wschod
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
        if ( prev_index != index && m_vLocations[index].uiSet != m_vLocations[prev_index].uiSet)
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
    akt=(m_vLocations[Wsp_A].Head)->Tail;
    //koniec zestawu A jako nastêpny wskazuje na poczatek zestawu B
    akt->Next=m_vLocations[Wsp_B].Head;
    do
    {
        akt=akt->Next;
        //zmien wskaznik na poczatek zestawu A
        akt->Head=m_vLocations[Wsp_A].Head;
        //ustaw taki sam kod zestawu
        akt->uiSet=(m_vLocations[Wsp_A].Head)->uiSet;
    }
    while((akt->Next)!=NULL);
    //poniewaz jestes na koncu zestawu B i koncu zestawu polaczonego
    //ustaw wskaznik w glowie zestawu polaczonego
    //na koniec polaczonego zestawu
    (m_vLocations[Wsp_A].Head)->Tail=akt;
}

void CMazeGeneratorPrivate::PrepareEdges()
{
    unsigned int index=0,index1=0,index2=0;
    unsigned int X=iSizeX,Y=iSizeY;
    index=0;
    for(index1=0; index1<Y; index1++)
        for(index2=0; index2<X-1; index2++)
        {
            m_vEdges[index].WspX1=index2;
            m_vEdges[index].WspY1=index1;
            m_vEdges[index].WspX2=index2+1;
            m_vEdges[index].WspY2=index1;
            m_vEdges[index].bActive=true;
            index++;
        }

    for(index1=0; index1<Y-1; index1++)
        for(index2=0; index2<X; index2++)
        {
            m_vEdges[index].WspX1=index2;
            m_vEdges[index].WspY1=index1;
            m_vEdges[index].WspX2=index2;
            m_vEdges[index].WspY2=index1+1;
            m_vEdges[index].bActive=true;
            index++;
        }
}

void CMazeGeneratorPrivate::RemoveEdge(unsigned int index1,unsigned int index2)
{
    unsigned int index=0,Count=0;
    unsigned int X1=0,X2=0,Y1=0,Y2=0;
    Krawedz	temp;
    X1=index1%iSizeX;
    Y1=index1/iSizeX;
    X2=index2%iSizeX;
    Y2=index2/iSizeX;
    Count=m_vEdges.size();
    for(index=0; index<Count; index++)
    {
        temp = m_vEdges[index];
        if  (( temp.WspX1 == X1 && temp.WspY1 == Y1
                && temp.WspX2 == X2 && temp.WspY2 == Y2 ) ||
                ( temp.WspX2 == X1 && temp.WspY2 == Y1
                  && temp.WspX1 == X2 && temp.WspY1 == Y2 ) )
        {
            m_vEdges[index].bActive=false;
            return;
        }
    }
}

void CMazeGeneratorPrivate::SetLocations()
{
    unsigned int index=0;
    for(index=0; index<m_EdgeCount; index++)
        if (m_vEdges[index].bActive==true)
        {
            if (m_vEdges[index].WspY1==m_vEdges[index].WspY2)
            {
                m_MazeData.m_vvMapa[m_vEdges[index].WspX1][m_vEdges[index].WspY1].right=true;
                m_MazeData.m_vvMapa[m_vEdges[index].WspX2][m_vEdges[index].WspY2].left=true;
            }
            else
            {
                m_MazeData.m_vvMapa[m_vEdges[index].WspX1][m_vEdges[index].WspY1].down=true;
                m_MazeData.m_vvMapa[m_vEdges[index].WspX2][m_vEdges[index].WspY2].up=true;
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

    for(X=1; X<=iSizeX; X++)
        for(Y=1; Y<=iSizeY; Y++)
        {
            m_MazeData.get_location(X,Y,up,down,right,left);
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
                else if (X == iSizeX && right)				dirs[2]=false;
                if (Y == 1 && up)		dirs[0]=false;
                else if (Y == iSizeY && down)				dirs[1]=false;

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

                pLoc = &m_MazeData.m_vvMapa[X-1][Y-1];
                pLoc1 = &m_MazeData.m_vvMapa[X1-1][Y1-1];
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
maze_generator::maze_generator():pimpl(new CMazeGeneratorPrivate)
{
}
maze_generator::~maze_generator()
{}

const maze & maze_generator::GenerateMaze(unsigned int MaxX ,unsigned int MaxY,EMazeTypes eMazeType)
{
    maze_settings xMazeSettings;
    xMazeSettings.size_x=MaxX;
    xMazeSettings.size_y=MaxY;
    xMazeSettings.mazeType=eMazeType;
    xMazeSettings.bMazePerfect=true;
    GenerateMaze(xMazeSettings);
	pimpl->m_MazeData.SetMazeEdges();
    return pimpl->m_MazeData;
}
const maze & maze_generator::GenerateMaze(const maze_settings & xMazeSettings)
{
    pimpl->PerformLocationReset();
    pimpl->iSizeX=xMazeSettings.size_x;
    pimpl->iSizeY=xMazeSettings.size_y;
    pimpl->AllocateLocationTable();

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
    return pimpl->m_MazeData;
}
