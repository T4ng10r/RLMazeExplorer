#include "maze_generator_kruskal.h"
#include "maze.h"
#include <time.h>
#include <algorithm>
#include <set>
#include <map>
#include <Tools/loggers.h>
#include <boost/format.hpp>
#include <time.h>       /* time */

const int empty_id_set(-1);
typedef std::map<unsigned int, int> location_sets_type;

class maze_generator_kruskal_private
{
public:
	maze_generator_kruskal_private();
    unsigned int make_id(unsigned int X, unsigned int Y);

	unsigned int get_bits_size(unsigned int);
	void reset_locations();
	void allocate_locations_table();
	void generate_edges();
	void generate_maze();
	void join_sets(unsigned int loc1, unsigned int loc2);
	void print_maze_status_debug();
	void MakeNotPerfect();

public:
	unsigned int                size_x, size_y;
	unsigned int                locations_id_mask;
	std::vector<unsigned int>	edges_sets;
	location_sets_type          locations_sets;
	std::shared_ptr<maze>     maze_data;
};

maze_generator_kruskal_private::maze_generator_kruskal_private() : maze_data(new maze){}
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

	unsigned int edge_count = 2 * size_x*size_y - size_y - size_x;
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
	for (unsigned int x = 0; x < size_x ; x++)
		for (unsigned int y = 0; y < size_y ; y++)
		{
			unsigned int edge_id;
			//get all left walls
			if (x < size_x - 1)
			{
				edge_id = make_id(x, y) + (make_id(x + 1, y) << locations_id_mask);
				edges_sets.push_back(edge_id);
			}
			if (y < size_y - 1)
			{
				edge_id = make_id(x, y) + (make_id(x, y + 1) << locations_id_mask);
				edges_sets.push_back(edge_id);
			}
		}
	srand(time(NULL));
	std::random_shuffle(edges_sets.begin(), edges_sets.end());
}
void maze_generator_kruskal_private::generate_maze()
{
	while (!edges_sets.empty())
	{
		unsigned int edge_id = edges_sets.back();
		unsigned int loc_2_id = edge_id >> locations_id_mask;
		unsigned int loc_1_id = edge_id - (loc_2_id << locations_id_mask);
		//sprawdz czy lokacje po obu stronach s� w tym samy zbiorze
		if (locations_sets[loc_1_id] != locations_sets[loc_2_id])
		{
			int x1 = loc_1_id % size_x;
			int x2 = loc_2_id % size_x;
			location& loc_1 = maze_data->get_xlocation(x1, loc_1_id / size_x);
			location& loc_2 = maze_data->get_xlocation(x2, loc_2_id / size_x);
			//je�lie nie - usu� scian� z obu lokacji i po��cz ich zbiory
			if (x1 == x2)
			{
				//remove up/bottom
				loc_1.set_passage(SOUTH_DIR);
				loc_2.set_passage(NORTH_DIR);
			} else {
				//remove left/right
				loc_1.set_passage(EAST_DIR);
				loc_2.set_passage(WEST_DIR);
			}
			join_sets(loc_1_id, loc_2_id);
		}
		edges_sets.pop_back();
	};
}
void maze_generator_kruskal_private::join_sets(unsigned int loc1, unsigned int loc2)
{
	unsigned int old_id = locations_sets[loc2];
	locations_sets[loc2] = locations_sets[loc1];
	unsigned int new_id = locations_sets[loc2];
	//find all entries which point on loc2 and change them to new loc2 target
	for (location_sets_type::iterator it = locations_sets.begin();
		 it != locations_sets.end(); it++)
	{
		if (it->second == old_id)
			it->second = new_id;
	}
}
//////////////////////////////////////////////////////////////////////////
unsigned int maze_generator_kruskal_private::make_id(unsigned int X, unsigned int Y)
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
        }*/
}
//////////////////////////////////////////////////////////////////////////
maze_generator_kruskal::maze_generator_kruskal() : pimpl(new maze_generator_kruskal_private){}
maze_generator_kruskal::~maze_generator_kruskal(){}
std::shared_ptr<maze_interface> maze_generator_kruskal::generate_maze(const maze_settings & settings)
{
	pimpl->size_x = settings.size_x;
	pimpl->size_y = settings.size_y;
	pimpl->allocate_locations_table();
	pimpl->maze_data->preset_maze_edges();
	pimpl->generate_edges();
	pimpl->generate_maze();
	return pimpl->maze_data;
}
