#ifndef YwZShSPlayer_hpp
#define YwZShSPlayer_hpp

#include "Piece.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include <iostream>
#include <vector>

namespace ECE141 {
    
    struct MoveOption {
        const Piece   *piece;
        Location      location;
        int           score;

        MoveOption(const Piece *p, Location l, int s):piece(p), location(l.row, l.col), score(s){};
    };

    class Game; //forward declare...

    class YwZShSPlayer : public Player {
    public:
        YwZShSPlayer();
        const PieceColor  color;
        static int        pcount; //how many created so far?
        virtual bool takeTurn(Game &aGame, Orientation aDirection, std::ostream &aLog);
    protected:
        bool isKingable(Game &aGame, const Piece &aPiece, const Location &aDest);
        int moveScore(Game &aGame, const Piece &aPiece, int aDeltaX, int aDeltaY);
        bool oppoNearBy(Game &aGame,const Location &aLoc, const Location& before, const PieceColor curColor);
        const Piece* isOpponent(Game &aGame, const Location &aLoc, int aDeltaX, int aDeltaY, const Location &before, const PieceColor curColor);
        bool capturedLoc(const Location &a, std::vector<Location> locs);
        bool canJumpTo(Game &aGame, const Location &aLoc, int aDeltaX, int aDeltaY, std::vector<Location> locs, const PieceColor curColor);
        Location* pieceHasJump(Game &aGame, const PieceKind pk, const Location &aLoc, const PieceColor curColor, std::vector<Location> locs);
        std::vector<Move> countAvailableMove(Game& aGame, Orientation aDirection, std::ostream &aLog, PieceColor curColor);

        int moreY(PieceColor aColor);
        int lessY(PieceColor aColor);
        int moreX(PieceColor aColor);
        int lessX(PieceColor aColor);
    };
}

#endif /* Player_hpp */
