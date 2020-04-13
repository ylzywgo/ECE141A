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

namespace ECE141 {


    int YwZShSPlayer::pcount = 0;
    static PieceColor autoColor1() { //auto assigns a color
        return (++YwZShSPlayer::pcount % 2) ? PieceColor::blue : PieceColor::gold;
    }
    YwZShSPlayer::YwZShSPlayer() : color(autoColor1()) {}


    bool YwZShSPlayer::isKingable(Game &aGame, const Piece &aPiece, const Location &aDest) {
        if(PieceKind::pawn==aPiece.getKind()) {
            return color == PieceColor::blue ? 0==aDest.row : (aGame.kBoardHeight-1)==aDest.row;
        }
        return false;
    }

    const Piece* YwZShSPlayer::isOpponent(Game &aGame, const Location &aLoc, int aDeltaX, int aDeltaY, const Location &before){
        Location near(aLoc.row+aDeltaY,aLoc.col+aDeltaX);
        if (const Tile *theTile=aGame.getTileAt(near)){
            const Piece* const thePiece=theTile->getPiece();
            if(thePiece && !thePiece->hasColor(color)) {
                std::cout << "cur loc: " <<  aLoc.row << " " << aLoc.col << std::endl;
                std::cout << "opponent: " <<  thePiece->getLocation().row << " " << thePiece->getLocation().col << std::endl;
                Location theJump(aLoc.row-aDeltaY,aLoc.col-aDeltaX);
                std::cout << "jump: " <<  theJump.row << " " << theJump.col << std::endl;
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

    bool YwZShSPlayer::oppoNearBy(Game &aGame, const Location &aLoc, const Location &before){
        if(isOpponent(aGame, aLoc, lessX(color), moreY(color), before) != nullptr) {
            return true;
        }
        if(isOpponent(aGame, aLoc, moreX(color), moreY(color), before) != nullptr) {
            return true;
        }
        const Piece* oppo;
        if((oppo = isOpponent(aGame, aLoc, lessX(color), lessY(color), before)) != nullptr && oppo->getKind() == PieceKind::king) {
            return true;
        }
        if((oppo = isOpponent(aGame, aLoc, moreX(color), lessY(color), before)) != nullptr && oppo->getKind() == PieceKind::king) {
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


    bool YwZShSPlayer::canJumpTo(Game &aGame, const Location &aLoc, int aDeltaX, int aDeltaY, std::vector<Location> locs) {
        Location theStep(aLoc.row+aDeltaY,aLoc.col+aDeltaX);
        if(const Tile *theTile=aGame.getTileAt(theStep)) {
            const Piece* const thePiece=theTile->getPiece();
            if(thePiece && !capturedLoc(thePiece->getLocation(), locs) && !thePiece->hasColor(color)) {
                Location theJump(theStep.row+aDeltaY,theStep.col+aDeltaX);
                if(const Tile *theTile=aGame.getTileAt(theJump)) {
                    return theTile->getPiece()==nullptr;
                }
            }
        }
        return false;
    }

    Location* YwZShSPlayer::pieceHasJump(Game &aGame, const PieceKind pk, const Location &aLoc, PieceColor aColor, std::vector<Location> locs) {
        if(canJumpTo(aGame, aLoc, lessX(aColor), moreY(aColor), locs)) {
            return new Location(moreY(aColor), lessX(aColor));
        }

        if(canJumpTo(aGame, aLoc, moreX(aColor), moreY(aColor), locs)) {
            return new Location(moreY(aColor), moreX(aColor));
        }

        if (PieceKind::king==pk) {
            if(canJumpTo(aGame, aLoc, lessX(aColor), lessY(aColor), locs)) {
                return new Location(lessY(aColor), lessX(aColor));
            }

            if(canJumpTo(aGame, aLoc, moreX(aColor), lessY(aColor), locs)) {
                return new Location(lessY(aColor), moreX(aColor));
            }
        }
        return nullptr;
    }

    int YwZShSPlayer::moveScore(Game &aGame, const Piece &aPiece, int aDeltaX, int aDeltaY) {
        int score = 0;
        std::vector<Location> locs;
        Location curLoc = aPiece.getLocation();
        if (canJumpTo(aGame, aPiece.getLocation(), aDeltaX, aDeltaY, locs)){
            score += 100;
            Location theStep(curLoc.row+aDeltaY,curLoc.col+aDeltaX);
            locs.push_back(theStep);
            Location theJump(curLoc.row+2*aDeltaY,curLoc.col+2*aDeltaX);
            PieceKind tmp = aPiece.getKind();
            Location* change;
            while ((change = pieceHasJump(aGame, tmp, theJump, color, locs)) != nullptr){
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
            if (oppoNearBy(aGame, curLoc, noNeed)){
                score += 15;
            }

            Location theStep(curLoc.row+aDeltaY,curLoc.col+aDeltaX);
            if(const Tile *theTile=aGame.getTileAt(theStep)) {
                const Piece* const thePiece=theTile->getPiece();
                if (!thePiece){
                    if (isKingable(aGame, aPiece, theStep))
                        score += 20;

                    if (oppoNearBy(aGame, theStep, curLoc)){
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

    int YwZShSPlayer::moreY(PieceColor aColor) {return PieceColor::blue==aColor ? -1 : 1;}
    int YwZShSPlayer::lessY(PieceColor aColor) {return PieceColor::blue==aColor ? 1 : -1;}
    int YwZShSPlayer::moreX(PieceColor aColor) {return PieceColor::blue==aColor ? 1 : -1;}
    int YwZShSPlayer::lessX(PieceColor aColor) {return PieceColor::blue==aColor ? -1 : 1;}
    bool YwZShSPlayer::takeTurn(Game &aGame, Orientation aDirection, std::ostream &aLog) {
        size_t theCount = aGame.countAvailablePieces(color);
        std::vector<MoveOption> options;
        for (int pos = 0; pos < theCount; pos++) {
            //NOTICE HOW WE CHECK FOR CAPTURED PIECES?
            if (const Piece *thePiece = aGame.getAvailablePiece(this->color, pos)) {
                int score;
                if ((score = moveScore(aGame, *thePiece, lessX(color), moreY(color))) != INT32_MIN) {
                    Location *newLoc;
                    if (score >= 100)
                        newLoc = new Location(thePiece->getLocation().row + 2 * moreY(color),
                                              thePiece->getLocation().col + 2 * lessX(color));
                    else
                        newLoc = new Location(thePiece->getLocation().row + moreY(color),
                                              thePiece->getLocation().col + lessX(color));

                    std::cout << "old location:" << thePiece->getLocation().row << " " << thePiece->getLocation().col
                              << std::endl;
                    std::cout << "new location:" << newLoc->row << " " << newLoc->col << std::endl;
                    std::cout << "score:" << score << std::endl;
                    MoveOption newMove(thePiece, *newLoc, score);
                    options.push_back(newMove);
                }

                if ((score = moveScore(aGame, *thePiece, moreX(color), moreY(color))) != INT32_MIN) {
                    Location *newLoc;
                    if (score >= 100)
                        newLoc = new Location(thePiece->getLocation().row + 2 * moreY(color),
                                              thePiece->getLocation().col + 2 * moreX(color));
                    else
                        newLoc = new Location(thePiece->getLocation().row + moreY(color),
                                              thePiece->getLocation().col + moreX(color));

                    std::cout << "old location:" << thePiece->getLocation().row << " " << thePiece->getLocation().col
                              << std::endl;
                    std::cout << "new location:" << newLoc->row << " " << newLoc->col << std::endl;
                    std::cout << "score:" << score << std::endl;
                    MoveOption newMove(thePiece, *newLoc, score);
                    options.push_back(newMove);
                }

                if (PieceKind::king == thePiece->getKind()) {
                    if ((score = moveScore(aGame, *thePiece, lessX(color), lessY(color))) != INT32_MIN) {
                        Location *newLoc;
                        if (score >= 100)
                            newLoc = new Location(thePiece->getLocation().row + 2 * lessY(color),
                                                  thePiece->getLocation().col + 2 * lessX(color));
                        else
                            newLoc = new Location(thePiece->getLocation().row + lessY(color),
                                                  thePiece->getLocation().col + lessX(color));

                        MoveOption newMove(thePiece, *newLoc, score);
                        options.push_back(newMove);
                    }

                    if ((score = moveScore(aGame, *thePiece, moreX(color), lessY(color))) != INT32_MIN) {
                        Location *newLoc;
                        if (score >= 100)
                            newLoc = new Location(thePiece->getLocation().row + 2 * lessY(color),
                                                  thePiece->getLocation().col + 2 * moreX(color));
                        else
                            newLoc = new Location(thePiece->getLocation().row + lessY(color),
                                                  thePiece->getLocation().col + moreX(color));

                        MoveOption newMove(thePiece, *newLoc, score);
                        options.push_back(newMove);
                    }
                }

            }
        }

        if (options.size() == 0)
            return false;

        std::sort(options.begin(), options.end(), [](MoveOption a, MoveOption b) { return a.score > b.score; });
        int maxScore = options[0].score;
        int index = 0;
        for (MoveOption option : options) {
            if (option.score == maxScore)
                index++;
            else
                break;
        }

        int rand = std::rand() % index;
        MoveOption maxMove = options[rand];

        std::cout << "------ turn:" << static_cast<std::underlying_type<PieceColor>::type>(color) << " "
                  << maxMove.piece->getLocation().row << maxMove.piece->getLocation().col << " " << maxMove.location.row
                  << maxMove.location.col << std::endl;
        aGame.movePieceTo(*(maxMove.piece), maxMove.location);

        Location *change;
        std::vector<Location> locs;
        while (maxMove.score >= 100 &&
               (change = pieceHasJump(aGame, maxMove.piece->getKind(), maxMove.location, color, locs)) != nullptr) {
            maxMove.location.row += 2 * change->row;
            maxMove.location.col += 2 * change->col;
            aGame.movePieceTo(*(maxMove.piece), maxMove.location);
        }
        std::cout << "end" << std::endl;
        return true;
    }
}
