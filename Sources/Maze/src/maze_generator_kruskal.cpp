#include "maze_generator_kruskal.h"
#include <time.h>
#include <algorithm>
#include <set>
#include <map>
#include <Tools/loggers.h>
#include <boost/format.hpp>

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

const int empty_id_set(-1);
typedef std::map<unsigned int, int> location_sets_type;

class maze_generator_kruskal_private
{
public:
	maze_generator_kruskal_private();
    unsigned int MakeID(unsigned int X, unsigned int Y);

	unsigned int get_bits_size(unsigned int);
	void reset_locations();
	void allocate_locations_table();
	void generate_edges();
	void generate_maze();
	void join_sets(unsigned int loc1, unsigned int loc2);
	void MakeNotPerfect();

public:
	unsigned int                size_x, size_y;
    unsigned int                edge_count;
	unsigned int                locations_id_mask;
	std::vector<unsigned int>	edges_sets;
	location_sets_type          locations_sets;
	boost::shared_ptr<maze>     maze_data;

};

maze_generator_kruskal_private::maze_generator_kruskal_private() :maze_data(new maze){}
unsigned int maze_generator_kruskal_private::get_bits_size(unsigned int test_value)
{
	unsigned int val(2);
	unsigned int bits_count(1);
	while (val < test_value)
	{
		val <<= 1;
		bits_count++;
	};
	return bits_count;
}
void maze_generator_kruskal_private::reset_locations()
{
    //int index1,index2;
	for (unsigned int index1 = 0; index1<size_x; index1++)
		for (unsigned int index2 = 0; index2<size_y; index2++)
            maze_data->m_vvMapa[index1][index2].reset();
}
void maze_generator_kruskal_private::allocate_locations_table()
{
	maze_data->size_x = size_x;
	maze_data->size_y = size_y;

    edge_count =  2*size_x*size_y-size_y-size_x ;
	locations_id_mask = get_bits_size(edge_count);

	maze_data->m_vvMapa.resize(size_x);
	for (unsigned int index = 0; index<size_x; index++)
		maze_data->m_vvMapa[index].resize(size_y);
	reset_locations();
	locations_sets.clear();
	for (unsigned int index = 0; index < size_x * size_y; index++)
		locations_sets[index] = index;
}
void maze_generator_kruskal_private::generate_edges()
{
	edges_sets.clear();
	for (unsigned int x = 0; x < size_x - 1; x++)
		for (unsigned int y = 0; y < size_y - 1; y++)
		{
			//get all left walls
			unsigned int edge_id = MakeID(x, y) + (MakeID(x+1, y) << locations_id_mask);
			edges_sets.push_back(edge_id);
			edge_id = MakeID(x, y) + (MakeID(x, y + 1) << locations_id_mask);
			edges_sets.push_back(edge_id);
			//return;
		}
		std::random_shuffle(edges_sets.begin(), edges_sets.end());
}
void maze_generator_kruskal_private::generate_maze()
{
	while (!edges_sets.empty())
	{
		unsigned int edge_id = edges_sets.back();
		unsigned int loc_2_id = edge_id >> locations_id_mask;
		unsigned int loc_1_id = edge_id - (loc_2_id << locations_id_mask);
		//sprawdz czy lokacje po obu stronach s¹ w tym samy zbiorze
		if (locations_sets[loc_1_id] != locations_sets[loc_2_id])
		{
			int x1 = loc_1_id % size_x;
			int x2 = loc_2_id % size_x;
			location& loc_1 = maze_data->get_xlocation(x1, loc_1_id / size_x);
			location& loc_2 = maze_data->get_xlocation(x2, loc_2_id / size_x);
			std::string log = str(boost::format("Location (%1%,%2%) and (%3%,%4%) are going to be joined") %
								  (loc_1_id % size_x) % (loc_1_id / size_x) % 
								  (loc_2_id % size_x) % (loc_2_id / size_x));
			//jeœlie nie - usuñ scianê z obu lokacji i po³¹cz ich zbiory
			if (x1 == x2)
			{
				log += "by NORTH/SOUTH";
				//remove up/bottom
				loc_1.set_passage(SOUTH_DIR);
				loc_2.set_passage(NORTH_DIR);
			} else {
				log += "by EAST/WEST";
				//remove left/right
				loc_1.set_passage(EAST_DIR);
				loc_2.set_passage(WEST_DIR);
			}
			printLog(eDebug, eDebugLogLevel, log);
			join_sets(loc_1_id, loc_2_id);
		}
		edges_sets.pop_back();
	};
}
void maze_generator_kruskal_private::join_sets(unsigned int loc1, unsigned int loc2)
{
	if (locations_sets[loc1] == loc1)
	{
		locations_sets[loc2] = loc1;
	}
	else {
		locations_sets[loc2] = locations_sets[locations_sets[loc2]];
	}
	unsigned int new_id = locations_sets[loc2];
	//find all entries which point on loc2 and change them to new loc2 target
	for (location_sets_type::iterator it = locations_sets.begin();
		 it != locations_sets.end(); it++)
	{
		if (it->second == loc2)
			it->second = new_id;
	}
}
//////////////////////////////////////////////////////////////////////////
unsigned int maze_generator_kruskal_private::MakeID(unsigned int X, unsigned int Y)
{
    return (X+Y*size_x);
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
maze_generator_kruskal::~maze_generator_kruskal(){}
boost::shared_ptr<maze_interface> maze_generator_kruskal::generate_maze(const maze_settings & settings)
{
	pimpl->size_x = settings.size_x;
	pimpl->size_y = settings.size_y;
    pimpl->allocate_locations_table();
	pimpl->maze_data->preset_maze_edges();
	pimpl->generate_edges();
	pimpl->generate_maze();
	/*
	unsigned int index = 0, index1 = 0;
	unsigned int Wsp_A = 0, Wsp_B = 0;
	unsigned int IleLaczen = 0;

	//tworzymy tablice z wszystkimi scianami wystepujacymi
	PrepareEdges();
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