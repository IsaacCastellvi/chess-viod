class piece
{
private:
    
public:

    char sprite = '#';
    piece();
    ~piece();
};

piece::piece()
{
}

//default deconstructor
piece::~piece()
{
}

// ####QUEEN
class queen : piece
{
private:
    /* data */
public:
    queen(/* args */);
    ~queen();
};

queen::queen(/* args */)
{
    sprite = '1';
}

queen::~queen()
{
}

class bishop : piece
{
private:
    /* data */
public:
    bishop(/* args */);
    ~bishop();
};

bishop::bishop(/* args */)
{
}

bishop::~bishop()
{
}

class horse : piece
{
private:
    /* data */
public:
    horse(/* args */);
    ~horse();
};

horse::horse(/* args */)
{
}

horse::~horse()
{
}

class rook
{
private:
    /* data */
public:
    rook(/* args */);
    ~rook();
};

rook::rook(/* args */)
{
}

rook::~rook()
{
}

class pawn
{
private:
    /* data */
public:
    pawn(/* args */);
    ~pawn();
};

pawn::pawn(/* args */)
{
}

pawn::~pawn()
{
}

