//
//  Game.cpp
//  Checkers
//
//  Created by rick gessner on 2/22/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include "Game.hpp"
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include <map>
#include <functional>

namespace ECE141 {
  
  using cspace = Location (*)(const Location &aLocation, int aScale);
  
  enum class Reasons {tbd, forfeit, badmove, eliminated, missedJump, moved2, clockExpired};
  
  static const size_t kMaxSize = Game::kBoardHeight;  //EVEN #
  static const size_t kMaxSteps = 700; //max # of steps before game is terminated...
  
  //------------------ utility ------------------------------
  
  Location noop(const Location &aLocation, int scale) {
    return aLocation;
  }
  
  Location heli(const Location &aLocation, int scale) {
    Location temp(aLocation.col, scale-1-aLocation.row);
    return temp;
  }
  
  Location martin(const Location &aLocation, int scale) {
    Location temp(scale-1-aLocation.col, aLocation.row);
    return temp;
  }
  
  Location q5av(const Location &aLocation, int scale) {
    Location temp(scale-1-aLocation.row, scale-1-aLocation.col);
//    std::cout << "q5av(" << temp.col <<"," << temp.row << ")" << std::endl;
    return temp;
  }
  
  //retrieve tile location...
  Location Tile::getLocation() const {return location;}
  
  //protected friend access to change kind...
  void Game::setKind(Piece &aPiece, PieceKind aKind) {
    aPiece.kind=aKind;
  }
  
  //protected friend access to change tile...
  void Game::setTile(Piece &aPiece, Tile *aTile) {
    aPiece.tile=aTile;
  }
  
  //protected friend access to change piece...
  void Game::setPiece(Tile &aTile,  Piece* aPiece) {
    aTile.piece=aPiece;
  }

  //----------------------------------------------

  class RealGame : public Game {
    
    std::vector<Piece*> goldPieces;
    std::vector<Piece*> bluePieces;
    std::vector<Tile>   tiles[kMaxSize];
    
    PieceColor  loserColor;
    Reasons     reason;
    float       priorDist;
    Piece*      priorPiece;
    const float stepLen;
    const float jumpLen;
    Orientation orientation;
    Player      *activePlayer;
    int         step;
    int         scale;
    size_t      steps;
    size_t      jumps;
    
  public:

    RealGame() : Game(), loserColor(PieceColor::blue), reason(Reasons::tbd),
      priorDist(0),  priorPiece(nullptr), stepLen(sqrt(2)), jumpLen(sqrt(2)*3), step(0),
      steps(0),jumps(0) {

      static TileColor theColors[2]={TileColor::light, TileColor::dark};
      int theColor=1;
        
      std::srand((unsigned int)std::time(nullptr)); // use current time as seed for random generator
      size_t theDelta = ((kMaxSize-kBoardHeight)/2)+1;
        
      scale=kBoardHeight==kMaxSize ? kBoardHeight : kBoardHeight+((std::rand() % theDelta) *2);
      orientation=Orientation::north; //by default
        
      for(int theRow=0;theRow<scale;theRow++) {
        for(int aColumn=0;aColumn<scale;aColumn++) {
          Location theLocation(theRow, aColumn);
          theColor=!theColor;
          tiles[theRow].push_back( ECE141::Tile(theColors[theColor], theLocation)) ;
        }
        theColor=!theColor;
      }
        
    }

    virtual ~RealGame() { //delete pieces from vectors...
      for(auto p : bluePieces) {delete p;}
      for(auto p : goldPieces) {delete p;}
    }
    
    //-- USE: setup the players on the board -----------------
    void initPieces() {
      //now put the pieces onto the tiles...
      int theCol=1;
      size_t theWidth = getBoardWidth();
      for(int theRow=2;theRow>=0;theRow--) {
        for(int col=theCol;col<theWidth;col+=2) {
          Piece * thePiece = new Piece(PieceColor::gold, &tiles[theRow][col]);
          goldPieces.push_back(thePiece);
          setPiece(tiles[theRow][col], thePiece);
        }
        theCol=!theCol;
      }

      for(int theRow=scale-3;theRow<scale;theRow++) {
        for(int col=theCol;col<scale;col+=2) {
          Piece * thePiece = new Piece(PieceColor::blue, &tiles[theRow][col]);
          bluePieces.push_back(thePiece);
          setPiece(tiles[theRow][col], thePiece);
        }
        theCol=!theCol;
      }
    }

    //-- USE: retrieve basic game properties...
    virtual size_t getBoardWidth() {return size_t(scale);}
    virtual size_t getBoardHeight() {return size_t(scale);}
    virtual size_t getPiecesPerPlayer() {return (scale/2)*3;}

    //-- USE: make sure location is legit -----------------
    bool validLocation(const Location &aLocation) {
      if(aLocation.row>=0 && aLocation.row<getBoardHeight()) {
        return (aLocation.col>=0 && aLocation.col<getBoardWidth());
      }
      return false;
    }

    //-- USE: return # of pieces on board for player -----------------
    size_t countAvailablePieces(PieceColor aColor) {
      auto theStart = PieceColor::blue==aColor ? bluePieces.begin() : goldPieces.begin();
      auto theEnd   = PieceColor::blue==aColor ? bluePieces.end() : goldPieces.end();
      
      size_t count=0;
      while (theStart != theEnd) {
        Piece *thePiece=(*theStart++);
        if(thePiece && thePiece->hasColor(aColor) && PieceKind::captured!=thePiece->getKind()) count++;
      }
      
      return count;
    }
    
    //-- USE: retrieve Nth piece for player (for analysis) -----------------
    virtual const Piece* const getAvailablePiece(PieceColor aColor, int anIndex) {
      std::vector<Piece*> *thePieces=PieceColor::blue==aColor
        ? &bluePieces : &goldPieces;
      int count=0;
      for(auto e: *thePieces) {
        if(e->hasColor(aColor) && PieceKind::captured!=e->getKind() && anIndex==count++) {
          return e;
        }
      }
      return nullptr;
    }
    
    //-- USE: [internal] retrieve game tile (if valid) -----------------
    virtual const Tile* const tileAt(const Location &aLocation) {
      return validLocation(aLocation) ? &tiles[aLocation.row][aLocation.col] : nullptr;
    }

    
    //-- USE: offer RO tile (usually for player analysis) -----------------
    virtual const Tile* const getTileAt(const Location &aLocation) {
      if(validLocation(aLocation)) {
        static std::map<Orientation, std::function<Location(const Location &, int)> > fluxcap {
          {Orientation::north, noop}, {Orientation::east,  heli},
          {Orientation::south, q5av}, {Orientation::west,  martin}};
        
        Location temp=fluxcap[orientation](aLocation, orientation);
        return &tiles[temp.row][temp.col];
      }
      return nullptr;
    }
    
    //-- USE: remove jumped piece -------------------------
    void removePieceAt(const Location &aLocation) {
      if(const Tile *theTile=tileAt(aLocation)) {
        if(theTile->getPiece()) {
          auto thePiece = const_cast<Piece*>(theTile->getPiece());
          setKind(*thePiece, PieceKind::captured);
          setPiece(*const_cast<Tile*>(theTile), nullptr);
        }
      }
    }

    int moreY(PieceColor aColor) {return PieceColor::blue==aColor ? -1 : 1;}
    int lessY(PieceColor aColor) {return PieceColor::blue==aColor ? 1 : -1;}
    int moreX(PieceColor aColor) {return PieceColor::blue==aColor ? 1 : -1;}
    int lessX(PieceColor aColor) {return PieceColor::blue==aColor ? -1 : 1;}
    
    //-- USE: see if valid jump exists at (deltaX, deltaY) for given piece...
    bool canJumpTo(const Piece &aPiece, int aDeltaX, int aDeltaY) {
      Location thePLoc = aPiece.getLocation();
      Location theStep(thePLoc.row+aDeltaY,thePLoc.col+aDeltaX);
      if(const Tile *theTile=tileAt(theStep)) {
        const Piece* const thePiece=theTile->getPiece();
        if(thePiece && !thePiece->hasColor(aPiece.getColor())) {
          Location theJump(theStep.row+aDeltaY,theStep.col+aDeltaX);
          if(const Tile *theTile=tileAt(theJump)) {
            return theTile->getPiece()==nullptr;
          }
        }
      }
      return false;
    }

    
    //-- USE: call to determine if player has any available jump...
    bool pieceHasJump(const Piece &aPiece, PieceColor aColor) {
      if(canJumpTo(aPiece, lessX(aColor), moreY(aColor))) {
        return true;
      }
      
      if(canJumpTo(aPiece, moreX(aColor), moreY(aColor))) {
        return true;
      }
      
      if (PieceKind::king==aPiece.getKind()) {
        if(canJumpTo(aPiece, lessX(aColor), lessY(aColor))) {
          return true;
        }
        
        if(canJumpTo(aPiece, moreX(aColor), lessY(aColor))) {
          return true;
        }
      }
      return false;
    }
    
    //-- USE: call to determine if player has any available jump...
    bool playerHasJumps(const Player &aPlayer) {
      PieceColor theColor = aPlayer.color;
      size_t theCount=countAvailablePieces(theColor);
      for(int i=0;i<theCount;i++) {
        const Piece *thePiece=getAvailablePiece(theColor,i);
        if(pieceHasJump(*thePiece, theColor)) {
          return true;
        }
      } //for
      return false;
    }

    //-- USE: check move distance between tiles ------------------------
    float distance(const Location &aSrc, const Location &aDest) {
      return sqrt(pow(aDest.col - aSrc.col, 2) + pow(aDest.row - aSrc.row, 2));
    }

    //-- USE: confirm that dest may be occupied -------------------------
    bool isAvailable(const Tile &aTile) {
      return (!aTile.getPiece()) && (TileColor::dark==aTile.getColor());
    }
    
    //-- USE: confirm piece can move that direction  -------------------
    float isValidDirection(const Piece &aPiece, const Location &aSrc, const Location &aDest) {
      if(PieceKind::pawn==aPiece.getKind()) {
        return aPiece.hasColor(PieceColor::gold) ? aSrc.row<aDest.row : aSrc.row>aDest.row;
      }
      return true;
    }
    
    //-- USE: determine whether kingable piece is opponent first row  ----
    float isKingable(const Piece &aPiece, const Location &aDest) {
      if(PieceKind::pawn==aPiece.getKind()) {
        return aPiece.hasColor(PieceColor::blue) ? 0==aDest.row : (scale-1)==aDest.row;
      }
      return false;
    }
    
    //-- USE: determine whether kingable piece is opponent first row  ----
    const Piece* jumpedOpponent(const Piece &aPiece, const Location &aDest) {
      Location thePLoc = aPiece.getLocation();
      int theRow = std::min(thePLoc.row, aDest.row)+1;
      int theCol = std::min(thePLoc.col, aDest.col)+1;
      Location theOppoLoc(theRow, theCol);
      if(const Tile *theTile=tileAt(theOppoLoc)) {
        if(theTile->getPiece()) {
          return theTile->getPiece()->hasColor(aPiece.getColor()) ? nullptr : theTile->getPiece();
        }
      }
      return nullptr;
    }
    
    //-- USE: ensure given piece can move to given tile... -----------
    bool isValidMove(const Piece &aPiece, const Tile &aSrc, const Tile &aDest) {
      float theDist = distance(aSrc.getLocation(), aDest.getLocation());
      if(theDist<=jumpLen && isAvailable(aDest)) {
        if(isValidDirection(aPiece, aSrc.getLocation(), aDest.getLocation())) {
          if(priorDist==stepLen) return false; //CANT take 2 steps with one piece...
          if(theDist>stepLen) {
            return jumpedOpponent(aPiece, aDest.getLocation())!=nullptr;
          }
          return true; //slide...
        }
      }
      return false;
    }
    
    //-- USE: Ensure user doesn't change pieces during multi-moves --------
    Reasons validatePiece(const Piece &aPiece) {
      Piece *thePiecePtr=(Piece*)&aPiece;
      if(priorPiece && (priorPiece!=thePiecePtr) && (aPiece.hasColor(activePlayer->color))) {
        return Reasons::moved2;
      }
      priorPiece=thePiecePtr;
      return Reasons::tbd;
    }
    
    //-- USE: accept player move, update game state ------------------
    bool movePieceTo(const Piece &aPiece, const Location &aDestination)  {
      reason=validatePiece(aPiece);
      if(Reasons::tbd==reason) {
        
       // float theDist = distance(aPiece.location, aDest.location);
        const Tile* theSrcTile=aPiece.getTile();
        Tile* theDestTile=(Tile*)tileAt(aDestination);
        
        if(isValidMove(aPiece, *theSrcTile, *theDestTile)) {
          setPiece(*const_cast<Tile*>(theSrcTile), nullptr);
          setPiece(*const_cast<Tile*>(theDestTile), &const_cast<Piece&>(aPiece));
          
          priorDist=stepLen;
          if(auto theOpponent = jumpedOpponent(aPiece, aDestination)) {
            priorDist=jumpLen;
            jumps++;
            removePieceAt(theOpponent->getLocation());
          }
          else {
            if(pieceHasJump(aPiece, activePlayer->color)) {
              reason=Reasons::missedJump;
              return false;
            }
            steps++;
          }

          setTile(const_cast<Piece&>(aPiece), theDestTile);

          if(isKingable(aPiece, aDestination)) {
            setKind(const_cast<Piece&>(aPiece), PieceKind::king);
          }
          
          return true;
        }
        else reason=Reasons::badmove;
      }
      loserColor = activePlayer->color;
      return false;
    }
    
    //-- USE: identify terminal condition for game -------------------------
    bool gameCanContinue(Player &aPlayer) {
      
      if(Reasons::tbd!=reason) return false; //someone already lost...
      
      if(step<kMaxSteps) {
        size_t blue_count = countAvailablePieces(PieceColor::blue);
        size_t gold_count = countAvailablePieces(PieceColor::gold);
        
        if(aPlayer.color==PieceColor::blue) {
          if(!blue_count) {
            loserColor = PieceColor::blue;
            reason=Reasons::eliminated;
          }
        }
        else {
          if(!gold_count) {
            loserColor = PieceColor::gold;
            reason=Reasons::eliminated;
          }
        }
        return blue_count*gold_count>0;
      }
      reason=Reasons::clockExpired;
      return false;
    }
    
    //-- USE: Print conclusing message to console... -------------------------
    PieceColor showGameResults(std::ostream &anOutput) {

      const char *theLoser=PieceColor::blue==loserColor ? "Blue" : "Gold";
      const char *theWinner=PieceColor::blue==loserColor ? "Gold" : "Blue";

      switch(reason) {
         case Reasons::eliminated:
          anOutput << theWinner << " has eliminated " << theLoser << " from the board.\n";
           break;
         case Reasons::badmove:
           anOutput << theLoser << " is disqualified for choosing an illegal move.\n";
           break;
         case Reasons::forfeit:
           anOutput << theLoser << " has forfeited the game.\n";
           break;
         case Reasons::missedJump:
          anOutput << theLoser << " has forfeited by missing a jump.\n";;
           break;
         case Reasons::moved2:
          anOutput << theLoser << " is disqualified for moving two pieces.\n";;
           break;
         case Reasons::clockExpired:
          anOutput << "Game terminated because the clock expired.\n";;
           break;
         case Reasons::tbd:
           anOutput << "Game terminated for an unknown reason.\n";
           break;
       }
      anOutput << steps << " steps, " << jumps << " jumps\n";
       return loserColor==PieceColor::blue ? PieceColor::gold : PieceColor::blue;
    }
    
    void showSeperator(std::ostream &anOutput, const char *aPrefix="") {
      anOutput << aPrefix;
      for(int i=0;i<scale;i++) std::cout << "---|";
      anOutput << std::endl;
    }
    
    //-- USE: dumps state of board to terminal... -------------------------
    void visualizeBoard(std::ostream &anOutput) {
      anOutput << std::endl << "  Step " << ++step << std::endl;
      showSeperator(anOutput, "   |");
      
      for(int row=0;row<scale;row++) {
        anOutput << std::setfill (' ') << std::setw(2) << row << " |";
        for(int col=0;col<scale;col++) {
          Location theLocation(row,col);
          auto &tile = tiles[row][col];
          if(!tile.getPiece()) {
            anOutput << " . |";
          }
          else {
            char theColor = tile.getPiece()->hasColor(PieceColor::blue) ? 'b' : 'g';
            if(PieceKind::king==tile.getPiece()->getKind()) theColor=toupper(theColor);
            anOutput << " " << theColor << " |";
          }
        }
        anOutput << std::endl;
        if(row<scale) showSeperator(anOutput, "   |");
      }
      
      anOutput  << "  ";
      for(int col=0;col<scale;col++) {
        anOutput << std::setfill (' ') << std::setw(4) << col;
      }
      anOutput << std::endl;
    }
    
    //-- USE: iterates player turns until end state  -------------------------
    PieceColor run(Player &aPlayer1, Player &aPlayer2, std::ostream &anOutput) {
      
      initPieces(); //once at the start of each game...
            
      activePlayer=&aPlayer1;
      while(Reasons::tbd==reason && gameCanContinue(*activePlayer)) {
        visualizeBoard(anOutput);
        //orientation=static_cast<Orientation>(std::rand() % 4);
        orientation=north;
        priorPiece=nullptr; //tracking multi-moves...
        
        if(!activePlayer->takeTurn(*this, orientation, anOutput)) {
          loserColor = activePlayer->color;
          reason=Reasons::forfeit;
        }
        else if(priorDist==jumpLen && pieceHasJump(*priorPiece, activePlayer->color)){
          loserColor = activePlayer->color; //piece should have made multi-jump!
          reason=Reasons::missedJump;
        }
        activePlayer = (activePlayer==&aPlayer1) ? &aPlayer2 : &aPlayer1;
        priorDist=0;
      }
      visualizeBoard(anOutput);

      return showGameResults(anOutput);
    }
    
  };

  //-- USE: game factory  -------------------------
  PieceColor Game::run(Player &aP1, Player &aP2, std::ostream &anOut) {
    RealGame theGame;
    return theGame.run(aP1, aP2, anOut);
  }
  
}
