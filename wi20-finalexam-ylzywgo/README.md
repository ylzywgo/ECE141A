# WI20-Final Game
## Instructions for taking this online exam

There are two parts to the exam: 1) an analysis part where you will answer questions about the game design, using principles taken from lecture, and 2) a coding part based on Homework 5.  We've designed the exam so that it's possible to complete the work in 2 hours. So...grab a beverage, make sure your zoom connection is on -- and let's get started.  

# 1. Analysis Section Overview 

For the following questions, write your answers inside a file called "analysis.txt" that you'll find located in your final project source folder.  It is our expectation that each question can be answered in 2-3 paragraphs (or less). 

## Analysis Question 1 - CRTP (25 pts)

In the String assignment #3 -- our Sortable interface used the CRTP. Explain the specific problem that the CRTP solves between a base class and a subclass. Write a brief explanation. 

---

> For the following questions, refer to the source code for the `Game` engine (excluding your customer `Player` class).

## Analysis Question 2 - Inversion of Control (25 pts)

Explain how the `Game` represents an example of the 'inversion of control' pattern. Write a brief explanation that defines "inversion of control", and provide examples from the code that illustrate your argument. 

---

## Analysis Question 3 - Object Relationships (25 pts)

We repeatedly discussed six types of relationships found in object-oriented solutions.  Find and describe examples that represents at least four (4) different object-relationship types. Each example should clearly describe the type of relationship, and specify a class, the filename, and the line where the example can be found. 

---

## Analysis Question 4 - RealGame  (25 pts)

Your player class gets access to a Game object, but that class is only a `Proxy`. The real work is done in the `RealGame` class. Why did we go to the trouble to built it this way?  What advantage does this design offer to the game?  Keep your answer specific and brief.  

---

## Analysis Question 5 (EXTRA CREDIT) - Code Review (20 pts.)
 
Review the Game.cpp file. Pay attention to code layout, comments, naming conventions (how things are named), and how the tasks are broken up into methods.  In your own words, describe how this code is written in comparison to your code. Is it easier or harder to follow? Is the logic obvious?  Does the code tell a story?  Identify coding practices that you like, or that you don't understand.  How might seeing this code change how you write your own code?

-----

# 2. Coding Section Overview

In assignment #5, you wrote a checker playing bot that followed the standard rules of checkers.  For your final, you'll update your game playing bot to work in a modified environment. You'll find four parts below, each of which is worth points toward the coding portion of your final grade. 

NOTE: You are expected to reuse your custom Checker-bot (player) files (.hpp/.cpp) from your assignment5 github repo. Updated versions of the other files from assignment5 (that you didn't create yourself) are included in this repository. Do NOT replace or change any of the other files in this repo unless specifically asked to do so.  

> You may not change any source files *other* than your own player class file without explicit permission.

It's important to realize that some of the other elements of the game engine have changed, and it's up to you to adapt your code to these changes. Most are very minor. Some add a new dimension to the game. 
 
## Part 1 (20 Points) -- Variable board size

In this part, you will have to adapt your player to deal with the fact that the size of the game board will vary between games. In the standard game, your board was fixed at an 8x8 grid. In this new version, your game board will vary from game to game, and from 8x8 to 12x12. To determine the length of a side of the board, you can call `Game.getBoardLength()`. 

> NOTE: Constants such as `kBoardHeight` and `kPiecesPerPlayer` are no longer available.

Depending on how you wrote your game, you may need to adapt some data structures in your player to account for the variable board size.

## Part 2 (20 pts) -- `movePieceTo` and `jumpPieceTo` 

In the previous version of the game from assignment #5, you would make both a "step" and a "jump' to the game by calling:

```
   virtual bool movePieceTo(const Piece &aPiece, const Location &aLocation)=0;
```

In this version of the game, these actions are separate. If you are taking a step during your turn, call `movePieceTo`. If you are jumping, call `jumpPieceTo`.  You can call `jumpPieceTo` multiple times if necessary to complete your turn.

```
   virtual bool movePieceTo(const Piece &aPiece, const Location &aLocation); //CALL THIS ONLY TO STEP 1 SQUARE!
   virtual bool jumpPieceTo(const Piece &aPiece, const Location &aLocation); //CALL THIS TO JUMP!   
```

## Part 3 (25pts) - Reporting The Moves of Your Available Pieces

A big part of this game was to identify your best move options. In this part -- you will report possible moves to the game engine. During each player turn, you must report the of possible moves for each of your available pieces:

```
    virtual void reportMove(const Move &aMove)=0;
```

To accomplish this task, you must create a `Move` object for each possible move, for each of your available pieces. `Move` is defined like this (you will find this in `Piece.hpp`):

```
  struct Move {
      
    Move(PieceKind aKind, MoveType aMove, int aScore,const Location &aStart, const Location &aDest) :
        kind(aKind), start(aStart), dest(aDest), move(aMove), score(aScore) {}
    
    Move(const Move &aCopy) :
        kind(aCopy.kind), start(aCopy.start), dest(aCopy.dest), move(aCopy.move), score(aCopy.score) {}
    
    PieceKind kind;  //can be PieceKind::pawn or PieceKind::king
    MoveType  move;  //can be MoveType::step or MoveType::jump
    int       score; //Score for each possible move (pass 0 if you didn't score moves)
    Location  start; //Where the piece is (before) it moves
    Location  dest;  //Where the piece wants to move to
  };
```

To complete this step, make one `Move` object for each possible move for all of your availabe pieces:

```
Move theMove(...args...); //describe a move for a given piece
game.reportMove(theMove); //do this for all moves for each piece
```


## Part 4 (35 pts) -- Setting a Trap For Your Opponent

Let your inner James Bond (spy) have some fun! In this step, you will set a trap for your opponent. 

During each player turn, *AFTER* you have instructed the game where you want to move a given piece, you can call a new `Game` method:

```
    virtual void  setTrapAt(const Location &aLocation);
```

Calling this method results the tile at a trap location to dangerous for your opponent.  Your opponent cannot tell where you have set your trap. If they land on the "trapped" tile during their turn, that piece is immediately eliminated from the board. You can only set one trap per turn. 


## Submit your work 

Once you've finished programming and TESTING your updated player, please commit your changes back to the new repository for github classroom.  Don't forget to update your student.json file.  

Don't forget to submit your repository to gradescope as well (as usual).

Once you've submitted your work, you may leave the zoom session. 


# GOOD LUCK EVERYONE!
