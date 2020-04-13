//
//  Player.hpp
//  Checkers
//
//  Created by rick gessner on 2/22/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "Piece.hpp"
#include <iostream>
#include <vector>

namespace ECE141 {
  
  class Game; //forward declare...  
  
  class Player {
  public:
                      Player();
    virtual bool      takeTurn(Game &aGame, Orientation aDirection, std::ostream &aLog);
    const PieceColor  color;
    static int        pcount; //how many created so far?
  };


}

#endif /* Player_hpp */
