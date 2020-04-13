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

  enum class PieceKind   {pawn, king, captured};
  enum class PieceColor  {gold, blue};
  enum class TileColor   {light, dark};
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
      : location(aLocation), piece(aPiece), color(aTileColor)   {
    }

    Tile(const Tile &aTile) : location(aTile.location), piece(aTile.piece), color(aTile.color) {}

    const Piece* const  getPiece() const {return piece;}
    Location            getLocation() const;
    const TileColor     getColor() const {return color;}
    
  private:
    const Location  location;
    Piece           *piece;
    TileColor       color;
    
    friend class Game;
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
    PieceKind         kind;
    const PieceColor  color;

    friend class Game;
    
  };
}
#endif /* Piece_hpp */
