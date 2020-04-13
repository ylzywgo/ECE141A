//  Piece.hpp
//
//  Created by rick gessner on 2/22/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//
#ifndef Piece_hpp
#define Piece_hpp

#include  "stdio.h"

namespace ECE141 {

  class Piece; //fwd-declare to avoid compile issue...

  enum class PieceKind    {pawn,  king, captured};
  enum class PieceColor   {gold,  blue};
  enum class TileColor    {light, dark};
  enum class MoveType     {step,  jump};

  enum       Orientation {north=0, east=1, south=2, west=3};
  
  //stores col, row for tiles, peices, etc.
  struct Location {
    int  col;
    int  row;
    Location(int aRow, int aCol) : col(aCol), row(aRow) {}
    Location(const Location &aCopy) : col(aCopy.col), row(aCopy.row) {}
  };
  
  //Single tile on the game board
  //NOTE: you HAVE to use the getter (accessor) methods to get properties
  
  struct Tile {
    Tile(TileColor aTileColor, Location aLocation, Piece *aPiece=nullptr)
      : location(aLocation), piece(aPiece), color(aTileColor), trap(false)   {
    }

    Tile(const Tile &aTile) :
      location(aTile.location), piece(aTile.piece), color(aTile.color), trap(aTile.trap) {}

    const Piece* const  getPiece() const {return piece;}
    Location            getLocation() const;
    const TileColor     getColor() const {return color;}
    
  private:
    
    Tile&               setTrap(bool aTrap) {trap=aTrap; return *this;}
    
    const Location  location;
    Piece           *piece;
    TileColor       color;
    bool            trap;
    
    friend class Game;
  };
  
  //--------------------------------------

  struct Move {
    Move(PieceKind aKind, MoveType aMove, int aScore,
         const Location &aStart, const Location &aDest) :
         kind(aKind), start(aStart), dest(aDest), move(aMove), score(aScore) {}
    
    Move(const Move &aCopy) :
      kind(aCopy.kind), start(aCopy.start), dest(aCopy.dest),
      move(aCopy.move), score(aCopy.score) {}
    
    PieceKind kind;  //can be PieceKind::pawn or PieceKind::king
    MoveType  move;  //can be MoveType::step or MoveType::jump
    int       score; //Score for each possible move (pass 0 if you didn't score moves)
    Location  start; //Where the piece is (before) it moves
    Location  dest;  //Where the piece wants to move to
  };

  //--------------------------------------
  
  //Defines game pieces on the board; 2 colors (gold, blue)
  //You MUST use getters to get piece properties
  class Piece {
  public:
    
    Piece(PieceColor aColor, Tile * const aTile, PieceKind aKind=PieceKind::pawn) :
      tile(aTile), kind(aKind), color(aColor) {
    }
    
    Location getLocation() const {
      return tile ? tile->getLocation() : Location(-1,-1);
    }
    
    const Tile* const getTile() const {return (const Tile* const)tile;}
    bool              hasColor(PieceColor aColor) const {return color==aColor;}
    PieceKind         getKind() const {return kind;}
    const PieceColor  getColor() const {return color;}

  private:
    
          Tile        *tile;
          PieceKind   kind;
    const PieceColor  color;

    friend class Game;
    
  };
}
#endif /* Piece_hpp */
