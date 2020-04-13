//
//  Player.cpp
//  Checkers
//
//  Created by rick gessner on 2/22/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include <vector>
#include <algorithm>
#include "Player.hpp"
#include "YwZShSPlayer.hpp"
#include "Game.hpp"
#include "Piece.hpp"

namespace ECE141 {


    int YwZShSPlayer::pcount = 0;
    static PieceColor autoColor1() { //auto assigns a color
        return (++YwZShSPlayer::pcount % 2) ? PieceColor::blue : PieceColor::gold;
    }
    YwZShSPlayer::YwZShSPlayer() : color(autoColor1()) {}


    bool YwZShSPlayer::isKingable(Game &aGame, const Piece &aPiece, const Location &aDest) {
        if(PieceKind::pawn==aPiece.getKind()) {
            return aPiece.getColor() == PieceColor::blue ? 0==aDest.row : (aGame.getBoardLength()-1)==aDest.row;
        }
        return false;
    }

    const Piece* YwZShSPlayer::isOpponent(Game &aGame, const Location &aLoc, int aDeltaX, int aDeltaY, const Location &before, const PieceColor curColor){
        Location near(aLoc.row+aDeltaY,aLoc.col+aDeltaX);
        if (const Tile *theTile=aGame.getTileAt(near)){
            const Piece* const thePiece=theTile->getPiece();
            if(thePiece && !thePiece->hasColor(curColor)) {
//                std::cout << "cur loc: " <<  aLoc.row << " " << aLoc.col << std::endl;
//                std::cout << "opponent: " <<  thePiece->getLocation().row << " " << thePiece->getLocation().col << std::endl;
                Location theJump(aLoc.row-aDeltaY,aLoc.col-aDeltaX);
//                std::cout << "jump: " <<  theJump.row << " " << theJump.col << std::endl;
                const Tile *jumpTile=aGame.getTileAt(theJump);
                if (jumpTile != nullptr) {
                    const Piece* const jumpPiece=jumpTile->getPiece();
                    if (jumpPiece &&( theJump.row != before.row || theJump.col != before.col))
                        return nullptr;
                    else
                        return theTile->getPiece();
                }
                else{
                    return nullptr;
                }
            }
            else{
                return nullptr;
            }
        }
        else{
            return nullptr;
        }
    }

    bool YwZShSPlayer::oppoNearBy(Game &aGame, const Location &aLoc, const Location &before, const PieceColor curColor){
        if(isOpponent(aGame, aLoc, lessX(curColor), moreY(curColor), before, curColor) != nullptr) {
            return true;
        }
        if(isOpponent(aGame, aLoc, moreX(curColor), moreY(curColor), before, curColor) != nullptr) {
            return true;
        }
        const Piece* oppo;
        if((oppo = isOpponent(aGame, aLoc, lessX(curColor), lessY(curColor), before, curColor)) != nullptr && oppo->getKind() == PieceKind::king) {
            return true;
        }
        if((oppo = isOpponent(aGame, aLoc, moreX(curColor), lessY(curColor), before, curColor)) != nullptr && oppo->getKind() == PieceKind::king) {
            return true;
        }
        return false;
    }

    bool YwZShSPlayer::capturedLoc(const Location &a, std::vector<Location> locs){
        for (Location b : locs){
            if ((a.row == b.row) && (a.col == b.col))
                return true;
        }
        return false;
    }


    bool YwZShSPlayer::canJumpTo(Game &aGame, const Location &aLoc, int aDeltaX, int aDeltaY, std::vector<Location> locs, const PieceColor curColor) {
        Location theStep(aLoc.row+aDeltaY,aLoc.col+aDeltaX);
        if(const Tile *theTile=aGame.getTileAt(theStep)) {
            const Piece* const thePiece=theTile->getPiece();
            if(thePiece && !capturedLoc(thePiece->getLocation(), locs) && !thePiece->hasColor(curColor)) {
                Location theJump(theStep.row+aDeltaY,theStep.col+aDeltaX);
                if(const Tile *theTile=aGame.getTileAt(theJump)) {
                    return theTile->getPiece()==nullptr;
                }
            }
        }
        return false;
    }

    Location* YwZShSPlayer::pieceHasJump(Game &aGame, const PieceKind pk, const Location &aLoc, const PieceColor curColor, std::vector<Location> locs) {
        if(canJumpTo(aGame, aLoc, lessX(curColor), moreY(curColor), locs, curColor)) {
            return new Location(moreY(curColor), lessX(curColor));
        }

        if(canJumpTo(aGame, aLoc, moreX(curColor), moreY(curColor), locs, curColor)) {
            return new Location(moreY(curColor), moreX(curColor));
        }

        if (PieceKind::king==pk) {
            if(canJumpTo(aGame, aLoc, lessX(curColor), lessY(curColor), locs, curColor)) {
                return new Location(lessY(curColor), lessX(curColor));
            }

            if(canJumpTo(aGame, aLoc, moreX(curColor), lessY(curColor), locs, curColor)) {
                return new Location(lessY(curColor), moreX(curColor));
            }
        }
        return nullptr;
    }

    int YwZShSPlayer::moveScore(Game &aGame, const Piece &aPiece, int aDeltaX, int aDeltaY) {
        int score = 0;
        std::vector<Location> locs;
        Location curLoc = aPiece.getLocation();
        if (canJumpTo(aGame, aPiece.getLocation(), aDeltaX, aDeltaY, locs, aPiece.getColor())){
            score += 100;
            Location theStep(curLoc.row+aDeltaY,curLoc.col+aDeltaX);
            locs.push_back(theStep);
            Location theJump(curLoc.row+2*aDeltaY,curLoc.col+2*aDeltaX);
            PieceKind tmp = aPiece.getKind();
            Location* change;
            while ((change = pieceHasJump(aGame, tmp, theJump, aPiece.getColor(), locs)) != nullptr){
                Location newStep(theJump.row + change->row, theJump.col + change->col);
                locs.push_back(newStep);
                theJump.row += 2 * change->row;
                theJump.col += 2 * change->col;
                score += 100;
                if (tmp != PieceKind::king && isKingable(aGame, aPiece, theJump)) {
                    tmp = PieceKind::king;
                    score += 20;
                }
            }
        }
        else{
            Location noNeed(-1, -1);
            if (oppoNearBy(aGame, curLoc, noNeed, aPiece.getColor())){
                score += 15;
            }
            Location theStep(curLoc.row+aDeltaY,curLoc.col+aDeltaX);
            if(const Tile *theTile=aGame.getTileAt(theStep)) {
                const Piece* const thePiece=theTile->getPiece();
                if (!thePiece){
                    if (isKingable(aGame, aPiece, theStep)) {
                        score += 20;
                    }
                    if (oppoNearBy(aGame, theStep, curLoc, aPiece.getColor())){
                        score -= 15;
                    }
                    else{
                        score += 10;
                    }
                }
                else{
                    return INT32_MIN;
                }
            }
            else{
                return INT32_MIN;
            }
        }
        return score;
    }

    std::vector<Move> YwZShSPlayer::countAvailableMove(Game& aGame, Orientation aDirection, std::ostream &aLog, PieceColor curColor) {
        size_t theCount = aGame.countAvailablePieces(curColor);
        std::vector<Move> options;
        for (int pos = 0; pos < theCount; pos++) {
            //NOTICE HOW WE CHECK FOR CAPTURED PIECES?
            if (const Piece *thePiece = aGame.getAvailablePiece(curColor, pos)) {
                int score;
                if ((score = moveScore(aGame, *thePiece, lessX(curColor), moreY(curColor))) != INT32_MIN) {
                    Location *newLoc;
                    if (score >= 100){
                        newLoc = new Location(thePiece->getLocation().row + 2 * moreY(curColor),
                                              thePiece->getLocation().col + 2 * lessX(curColor));
                        Move newMove(thePiece->getKind(), MoveType::jump, score, thePiece->getLocation(), *newLoc);
                        options.push_back(newMove);
                    }

                    else {
                        newLoc = new Location(thePiece->getLocation().row + moreY(curColor),
                                              thePiece->getLocation().col + lessX(curColor));
                        Move newMove(thePiece->getKind(), MoveType::step, score, thePiece->getLocation(), *newLoc);
                        options.push_back(newMove);
                    }

//                    std::cout << "old location:" << thePiece->getLocation().row << " " << thePiece->getLocation().col
//                              << std::endl;
//                    std::cout << "new location:" << newLoc->row << " " << newLoc->col << std::endl;
//                    std::cout << "score:" << score << std::endl;
                }

                if ((score = moveScore(aGame, *thePiece, moreX(curColor), moreY(curColor))) != INT32_MIN) {
                    Location *newLoc;
                    if (score >= 100){
                        newLoc = new Location(thePiece->getLocation().row + 2 * moreY(curColor),
                                              thePiece->getLocation().col + 2 * moreX(curColor));
                        Move newMove(thePiece->getKind(), MoveType::jump, score, thePiece->getLocation(), *newLoc);
                        options.push_back(newMove);
                    }
                    else{
                        newLoc = new Location(thePiece->getLocation().row + moreY(curColor),
                                              thePiece->getLocation().col + moreX(curColor));
                        Move newMove(thePiece->getKind(), MoveType::step, score, thePiece->getLocation(), *newLoc);
                        options.push_back(newMove);
                    }

//                    std::cout << "old location:" << thePiece->getLocation().row << " " << thePiece->getLocation().col
//                              << std::endl;
//                    std::cout << "new location:" << newLoc->row << " " << newLoc->col << std::endl;
//                    std::cout << "score:" << score << std::endl;
                }

                if (PieceKind::king == thePiece->getKind()) {
                    if ((score = moveScore(aGame, *thePiece, lessX(curColor), lessY(curColor))) != INT32_MIN) {
                        Location *newLoc;
                        if (score >= 100){
                            newLoc = new Location(thePiece->getLocation().row + 2 * lessY(curColor),
                                                  thePiece->getLocation().col + 2 * lessX(curColor));
                            Move newMove(thePiece->getKind(), MoveType::jump, score, thePiece->getLocation(), *newLoc);
                            options.push_back(newMove);
                        }
                        else{
                            newLoc = new Location(thePiece->getLocation().row + lessY(curColor),
                                                  thePiece->getLocation().col + lessX(curColor));
                            Move newMove(thePiece->getKind(), MoveType::step, score, thePiece->getLocation(), *newLoc);
                            options.push_back(newMove);
                        }
                    }

                    if ((score = moveScore(aGame, *thePiece, moreX(curColor), lessY(curColor))) != INT32_MIN) {
                        Location *newLoc;

                        if (score >= 100){
                            newLoc = new Location(thePiece->getLocation().row + 2 * lessY(curColor),
                                                  thePiece->getLocation().col + 2 * moreX(curColor));
                            Move newMove(thePiece->getKind(), MoveType::jump, score, thePiece->getLocation(), *newLoc);
                            options.push_back(newMove);
                        }
                        else{
                            newLoc = new Location(thePiece->getLocation().row + lessY(curColor),
                                                  thePiece->getLocation().col + moreX(curColor));
                            Move newMove(thePiece->getKind(), MoveType::step, score, thePiece->getLocation(), *newLoc);
                            options.push_back(newMove);
                        }
                    }
                }

            }
        }

        return options;
    }

    int YwZShSPlayer::moreY(PieceColor aColor) {return PieceColor::blue==aColor ? -1 : 1;}
    int YwZShSPlayer::lessY(PieceColor aColor) {return PieceColor::blue==aColor ? 1 : -1;}
    int YwZShSPlayer::moreX(PieceColor aColor) {return PieceColor::blue==aColor ? 1 : -1;}
    int YwZShSPlayer::lessX(PieceColor aColor) {return PieceColor::blue==aColor ? -1 : 1;}
    bool YwZShSPlayer::takeTurn(Game &aGame, Orientation aDirection, std::ostream &aLog) {
        std::vector<Move> options = countAvailableMove(aGame, aDirection, aLog, color);
        if (options.size() == 0)
            return false;

        std::sort(options.begin(), options.end(), [](Move a, Move b) { return a.score > b.score; });
        int maxScore = options[0].score;
        int index = 0;
        for (Move option : options) {
            if (option.score == maxScore)
                index++;
            else
                break;
        }

        int rand = std::rand() % index;
        Move maxMove = options[rand];
        const Piece* maxPiece = aGame.getTileAt(maxMove.start)->getPiece();

//        std::cout << "------ turn:" << static_cast<std::underlying_type<PieceColor>::type>(color) << " "
//                  << maxMove.piece->getLocation().row << maxMove.piece->getLocation().col << " " << maxMove.location.row
//                  << maxMove.location.col << std::endl;
        if (maxMove.score >= 100)
            aGame.jumpPieceTo(*(maxPiece), maxMove.dest);
        else
            aGame.movePieceTo(*(maxPiece), maxMove.dest);

        aGame.reportMove(maxMove);

        if (isKingable(aGame, *maxPiece, maxMove.dest) && maxMove.kind != PieceKind::king)
            maxMove.kind = PieceKind::king;

        Location *change;
        std::vector<Location> locs;
        while (maxMove.score >= 100 &&
               (change = pieceHasJump(aGame, maxPiece->getKind(), maxMove.dest, maxPiece->getColor(), locs)) != nullptr) {
            maxMove.dest.row += 2 * change->row;
            maxMove.dest.col += 2 * change->col;
            aGame.jumpPieceTo(*(maxPiece), maxMove.dest);
            aGame.reportMove(maxMove);
            if (isKingable(aGame, *maxPiece, maxMove.dest) && maxMove.kind != PieceKind::king) {
                maxMove.kind = PieceKind::king;
                std::cout << "become king" << std::endl;
            }
        }

        PieceColor oppoColor;
        if (color == PieceColor::blue)
            oppoColor = PieceColor::gold;
        else
            oppoColor = PieceColor::blue;

        std::vector<Move> oppoOps = countAvailableMove(aGame, aDirection, aLog, oppoColor);

        if (oppoOps.size() == 0)
            return true;

//        std::cout << "trap" << std::endl;

        std::sort(oppoOps.begin(), oppoOps.end(), [](Move a, Move b) { return a.score > b.score; });
        int maxOppoScore = oppoOps[0].score;
        index = 0;
        for (Move option : oppoOps) {
            if (option.score == maxOppoScore)
                index++;
            else
                break;
        }

        int randOppo = std::rand() % index;
        Move maxOppoMove = options[randOppo];
        aGame.setTrapAt(maxOppoMove.dest);

        std::cout << "end" << std::endl;
        return true;
    }
}
