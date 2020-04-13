//
//  main.cpp
//  Checkers
//
//  Created by rick gessner on 2/22/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include "Game.hpp"
#include "Player.hpp"
#include "YwZShSPlayer.hpp"
#include <iostream>
#include <sstream>
#include "Writable.hpp"

int main(int argc, const char * argv[]) {
    
  std::stringstream theOutput; 

  ECE141::YwZShSPlayer player1;
  ECE141::YwZShSPlayer player2;

  ECE141::Game::run(player1,player2, theOutput, true);

  ECE141::Writable theWritable;
  theWritable.save(theOutput);

  return 0;
}
