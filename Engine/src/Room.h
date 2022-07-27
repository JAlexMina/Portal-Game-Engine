#ifndef ROOM_H
#define ROOM_H


class Room
{
public:
    Room();

    int l = 0;
    int x = 0;
    int y = 0;
    bool visited = false;
    int walls[4] = {-1, -1, -1, -1}; // {N, S, E, W}
    Room* lr;
};

#endif // ROOM_H
