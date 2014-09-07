#ifndef C_LOCATION_H
#define C_LOCATION_H
#include <vector>
#include <deque>

class location	//jesli dany kierunek jest prawda - tam jest sciana
{
public:
	location()
    {
		reset();
    }
	//bit set if their's wall, otherwise it's false
	std::vector<bool> directions;
	//TRUE - if wall
	//FALSE - if free
    bool up;
    bool down;
    bool left;
    bool right;
    void reset()
    {
		directions = std::vector<bool>(4, false);
        up=false;
        down=false;
        left=false;
        right=false;
    }
};
#endif
