//
//  Game.hpp
//  Checkers
//
//  Created by rick gessner on 2/22/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "Player.hpp"
#include "Piece.hpp"
#include "stdio.h"
#include <iostream>
#include <vector>

namespace ECE141 {
  
  class Game {
  public:
                
    static  PieceColor          run(Player &aP1, Player &aP2, std::ostream &anOutput, bool showBoard=true); //call from main
    
      //The following methods are used by your player to interact with game...

    virtual size_t              countAvailablePieces(PieceColor aColor)=0;
    virtual const Piece* const  getAvailablePiece(PieceColor aColor, int anIndex)=0;
    virtual const Tile* const   getTileAt(const Location &aLocation)=0;
    virtual size_t              getBoardLength()=0;
    virtual size_t              getPiecesPerPlayer()=0;

    
    virtual bool                movePieceTo(const Piece &aPiece, const Location &aLocation)=0;
    virtual bool                jumpPieceTo(const Piece &aPiece, const Location &aLocation)=0;

    virtual void                reportMove(const Move &aMove)=0;
    virtual void                setTrapAt(const Location &aLocation)=0;
    
    protected:
    
    void setKind(Piece &aPiece, PieceKind aKind);
    void setTile(Piece &aPiece, Tile* aTile);
    void setPiece(Tile &aTile,  Piece* aPiece);
    void setTrap(Tile &aTile,  bool aTrap);

  };
}

#endif /* Game_hpp */
