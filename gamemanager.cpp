#include "gamemanager.h"
#include <iostream>
#include "pieces.h"
#include "Board.h"
#include <memory>
// using smart pointers for automatic memory managements

/*LAYOUT
r n b q k b n r
p p p p p p p p
# # # # # # # #
# # # # # # # #
# # # # # # # #
# # # # # # # #
P P P P P P P P
R N B Q K B N R
*/

void initGame(std::vector<std::vector<char>> & table,int lines = 2){
    table.assign(8, std::vector<char>(8, '#'));

    // Black pieces
    char blackBack[] = {'r','n','b','q','k','b','n','r'};
    for (int j = 0; j < 8; j++) {
        table[0][j] = blackBack[j];
        table[1][j] = 'p';
    }

    // White pieces
    char whiteBack[] = {'R','N','B','Q','K','B','N','R'};
    for (int j = 0; j < 8; j++) {
        table[6][j] = 'P';
        table[7][j] = whiteBack[j];
    }
}



std::vector<std::vector<std::shared_ptr<piece>>> InitializeBoard() {
    std::vector<std::vector<std::shared_ptr<piece>>> board(8, 
        std::vector<std::shared_ptr<piece>>(8, nullptr));
    
    // BLACK pieces at TOP (rows 0-1 = ranks 8-7)
    // Row 0: Black major pieces (Rank 8)
    board[0][0] = std::make_shared<rook>(false);     // A8
    board[0][1] = std::make_shared<knight>(false);   // B8
    board[0][2] = std::make_shared<bishop>(false);   // C8
    board[0][3] = std::make_shared<queen>(false);    // D8
    board[0][4] = std::make_shared<king>(false);     // E8
    board[0][5] = std::make_shared<bishop>(false);   // F8
    board[0][6] = std::make_shared<knight>(false);   // G8
    board[0][7] = std::make_shared<rook>(false);     // H8
    
    // Row 1: Black pawns (Rank 7)
    for (int i = 0; i < 8; i++) {
        board[1][i] = std::make_shared<pawn>(false); // A7-H7
    }
    
    // WHITE pieces at BOTTOM (rows 6-7 = ranks 2-1)
    // Row 6: White pawns (Rank 2)
    for (int i = 0; i < 8; i++) {
        board[6][i] = std::make_shared<pawn>(true);  // A2-H2
    }
    
    // Row 7: White major pieces (Rank 1)
    board[7][0] = std::make_shared<rook>(true);      // A1
    board[7][1] = std::make_shared<knight>(true);    // B1
    board[7][2] = std::make_shared<bishop>(true);    // C1
    board[7][3] = std::make_shared<queen>(true);     // D1
    board[7][4] = std::make_shared<king>(true);      // E1
    board[7][5] = std::make_shared<bishop>(true);    // F1
    board[7][6] = std::make_shared<knight>(true);    // G1
    board[7][7] = std::make_shared<rook>(true);      // H1
    
    // Set initial positions
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] != nullptr) {
                board[i][j]->Pos = Vector2{i, j};
            }
        }
    }
    
    return board;
}

//##############################################################################
//##################### CONVERISON ##############################################
//###############################################################################
Vector2 ConvertChessNotation(const std::string& notation) {
    if (notation.length() < 2) return Vector2{-1, -1};
    
    char file = toupper(notation[0]);  // A-H
    char rank = notation[1];           // 1-8
    
    if (file < 'A' || file > 'H' || rank < '1' || rank > '8') {
        return Vector2{-1, -1};
    }
    
    // RANK 1 is at TOP (array row 0), RANK 8 at BOTTOM (array row 7)
    int x = (rank - '1');  // '1' -> 0, '2' -> 1, ..., '8' -> 7
    int y = file - 'A';    // 'A' -> 0, 'B' -> 1, ..., 'H' -> 7
    
    //ADDING FOR CONVERSION BUGS
    std::cout << "DEBUG CONVERSION: " << notation << " -> [" << x << "," << y << "]\n";
    return Vector2{x, y};
}

std::string ConvertToChessNotation(const Vector2& pos) {
    if (pos.x < 0 || pos.x > 7 || pos.y < 0 || pos.y > 7) {
        return "??";
    }
    
    std::string notation;
    notation += 'A' + pos.y;        // Column letter A-H
    notation += '1' + pos.x;        // Row number 1-8 (simple!)
    return notation;
}

//##############################################################################
//##################### CHECK.CHECKMATE ##############################################
//###############################################################################
// find specific player king
Vector2 FindKingPosition(const std::vector<std::vector<std::shared_ptr<piece>>>& board, bool findWhiteKing) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != nullptr && dynamic_cast<king*>(board[i][j].get()) != nullptr) {
                if (board[i][j]->isWhite == findWhiteKing) {
                    return Vector2{i, j};
                }
            }
        }
    }
    return Vector2{-1, -1};
}

// specific king in check
bool IsKingInCheck(const std::vector<std::vector<std::shared_ptr<piece>>>& board, bool isWhiteKing) {
    Vector2 kingPos = FindKingPosition(board, isWhiteKing);
    if (kingPos.x == -1) return false;
    
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != nullptr && board[i][j]->isWhite != isWhiteKing) {
                Vector2 targetPos = kingPos;
                if (board[i][j]->isValidMove(targetPos, board)) {
                    return true;
                }
            }
        }
    }
    return false;
}

// return true if a move would leave your king in check
bool DoesMoveCauseSelfCheck(std::vector<std::vector<std::shared_ptr<piece>>>& board, const Vector2& from, const Vector2& to, bool isWhite) {
    // calculated trougth creating a future copy of the outcome,could plan on adding a danger property on cell based on specific piece position
    auto tempBoard = board;
    
    // Move piece on copy
    if (tempBoard[from.x][from.y]) {
        tempBoard[to.x][to.y] = tempBoard[from.x][from.y];
        tempBoard[from.x][from.y] = nullptr;
        tempBoard[to.x][to.y]->Pos = to;
        
        // Check if king is in check now
        return IsKingInCheck(tempBoard, isWhite);
    }
    return true;
}

// check if player has any safe move
bool HasAnyLegalMove(std::vector<std::vector<std::shared_ptr<piece>>>& board, bool isWhite) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] != nullptr && board[i][j]->isWhite == isWhite) {
                // Try all squares
                for (int x = 0; x < board.size(); x++) {
                    for (int y = 0; y < board[x].size(); y++) {
                        Vector2 from{i, j};
                        Vector2 to{x, y};
                        if (board[i][j]->isValidMove(to, board)) {
                            if (!DoesMoveCauseSelfCheck(board, from, to, isWhite)) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
//#################################################################################


EndCond GameLoop(std::vector<std::vector<std::shared_ptr<piece>>> &board) {
    bool whiteTurn = true;
    int Hindex;
    int turnCount = 1;
    int movesWithoutCapture = 0;
    std::string input;
    
    while (true) {
        // Display board and turn info
        std::cout << "\n=======================================\n";
        std::cout << "Turn " << turnCount << " - ";
        if (whiteTurn) {
            std::cout << "White's turn (uppercase pieces)\n";
        } else {
            std::cout << "Black's turn (lowercase pieces)\n";
        }
        std::cout << "=======================================\n\n";
        
        DrawTableObjects(board);
        //##########################################
        //#                 CHECKS                 #
        //##########################################

        // Check for end conditions - Kings exist?
        bool whiteKingExists = false;
        bool blackKingExists = false;
        
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] != nullptr) {
                    // Check if it's a king
                    auto piecePtr = board[i][j];
                    if (dynamic_cast<king*>(piecePtr.get()) != nullptr) {
                        if (piecePtr->isWhite) whiteKingExists = true;
                        else blackKingExists = true;
                    }
                }
            }
        }
        
        if (!whiteKingExists) {
            std::cout << "\nWhite king has been captured!\n";
            return EndCond::BLACKWIN;
        }
        if (!blackKingExists) {
            std::cout << "\nBlack king has been captured!\n";
            return EndCond::WHITEWIN;
        }
        
        // Check for 50-move rule sugested by ai
        if (movesWithoutCapture >= 100) {
            std::cout << "\nDraw by 50-move rule!\n";
            return EndCond::DRAW;
        }
        // Check if king is in check
        bool inCheck = IsKingInCheck(board, whiteTurn);
        if (inCheck) {
            std::cout << "\nCHECK! Your king is under attack! 0;| \n";
        }

        // Check for checkmate/stalemate
        bool hasLegalMoves = HasAnyLegalMove(board, whiteTurn);
        if (!hasLegalMoves) {
            if (inCheck) {
                std::cout << "\n CHECKMATE! " 
                        << (whiteTurn ? "Black" : "White") << " wins! \n";
                return whiteTurn ? EndCond::BLACKWIN : EndCond::WHITEWIN;
            } else {
                std::cout << "\n STALEMATE! Draw! |= \n ";
                return EndCond::DRAW;
            }
        }

        // transformn notations
        Vector2 selectedPiece;
        bool validSelection = false;
        
        while (!validSelection) {
            std::cout << "\nSelect your piece (e.g., E2, G1, etc.): ";
            std::cin >> input;
            
        
            if (input == "resign" || input == "RESIGN") {
                if (whiteTurn) {
                    std::cout << "\nWhite resigns! Black wins.\n";
                    return EndCond::BLACKWIN;
                } else {
                    std::cout << "\nBlack resigns! White wins.\n";
                    return EndCond::WHITEWIN;
                }
            }
            
            if (input == "draw" || input == "DRAW") {
                std::cout << "\nDraw offer. Does opponent accept? (y/n): ";
                std::string response;
                std::cin >> response;
                if (response == "y" || response == "Y") {
                    std::cout << "Both players agree to a draw.\n";
                    return EndCond::DRAW;
                } else {
                    std::cout << "Draw offer declined. Continue playing.\n";
                    continue;
                }
            }
            
            if (input == "help" || input == "HELP") {
                std::cout << "\nCommands:\n";
                std::cout << "- Enter moves as 'E2 E4' (piece square then target square)\n";
                std::cout << "- Type 'resign' to resign\n";
                std::cout << "- Type 'draw' to offer a draw\n";
                std::cout << "- Type 'help' to show this help\n";
                std::cout << "- Type 'cancel' to choose a different piece\n";
                continue;
            }
            
            selectedPiece = ConvertChessNotation(input);
            
            // Validate 
            if (selectedPiece.x < 0 || selectedPiece.x >= board.size() ||
                selectedPiece.y < 0 || selectedPiece.y >= board[0].size()) {
                std::cout << "Invalid notation! Use format like 'E2', 'G1', etc. (A-H, 1-8)\n";
                continue;
            }
            
            // Check for empty
            if (board[selectedPiece.x][selectedPiece.y] == nullptr) {
                std::cout << "No piece at " << input << "! Try again.\n";
                continue;
            }
            
            // Check beloging to parent
            if (board[selectedPiece.x][selectedPiece.y]->isWhite != whiteTurn) {
                std::cout << "That's not your piece! Try again.\n";
                continue;
            }
            
            validSelection = true;
        }
        
        // Show selected
        auto selectedPiecePtr = board[selectedPiece.x][selectedPiece.y];
        std::cout << "\nSelected: " << input << " (" 
                  << selectedPiecePtr->Sprite << ") - ";
        
        // check piece trougth casting
        if (dynamic_cast<pawn*>(selectedPiecePtr.get())) std::cout << "Pawn";
        else if (dynamic_cast<rook*>(selectedPiecePtr.get())) std::cout << "Rook";
        else if (dynamic_cast<knight*>(selectedPiecePtr.get())) std::cout << "Knight";
        else if (dynamic_cast<bishop*>(selectedPiecePtr.get())) std::cout << "Bishop";
        else if (dynamic_cast<queen*>(selectedPiecePtr.get())) std::cout << "Queen";
        else if (dynamic_cast<king*>(selectedPiecePtr.get())) std::cout << "King";
        std::cout << "\n";
        
        // Get target position in chess notation
        Vector2 targetPos;
        bool validMove = false;
        
        while (!validMove) {
            std::cout << "Move to (e.g., E4, D5, etc.) or 'cancel': ";
            std::cin >> input;
            // SKIP CHECK
            //board[selectedPiece.x][selectedPiece.y]->Pos = selectedPiece;
            if (input == "cancel" || input == "CANCEL") {
                std::cout << "Move cancelled. Select a different piece.\n";
                break; 
            }
            
            if (input == "help" || input == "HELP") {
                std::cout << "Enter the square where you want to move your piece.\n";
                std::cout << "Examples: E4, D5, G6, etc.\n";
                continue;
            }
            
            targetPos = ConvertChessNotation(input);
            
            // Validate coordinates
            if (targetPos.x < 0 || targetPos.x >= board.size() ||
                targetPos.y < 0 || targetPos.y >= board[0].size()) {
                std::cout << "Invalid notation! Use format like 'E4', 'D5', etc. (A-H, 1-8)\n";
                continue;
            }
            
            // Check if moving to same square,not intended nor represented in move vectors but player can still do it )=
            if (targetPos.x == selectedPiece.x && targetPos.y == selectedPiece.y) {
                std::cout << "Cannot move to the same square! Try again or type 'cancel'.\n";
                continue;
            }
            
            // **HARDCODED a7 pawn fix**
            if (selectedPiece.x == 6 - Hindex && selectedPiece.y == 0) {  // A7 position
                board[6][0]->Pos = Vector2{6, 0};
                Hindex--;
            }

            // validate func
            if (selectedPiecePtr->isValidMove(targetPos, board)) {
                validMove = true;
            } else {
                std::cout << "Invalid move for this piece! Try again or type 'cancel' to choose different piece.\n";
            }
        }
        
        if (!validMove) {
            continue;  // Go back to piece selection
        }
        
        // capture
        bool wasCapture = (board[targetPos.x][targetPos.y] != nullptr);
        
        if (wasCapture) {
            auto capturedPiece = board[targetPos.x][targetPos.y];
            std::cout << "\nCapturing " << capturedPiece->Sprite 
                      << " at " << ConvertToChessNotation(targetPos) << "!\n";
        }
        
        // Execute the move
        Vector2 moveDelta = {targetPos.x - selectedPiece.x, targetPos.y - selectedPiece.y};
        selectedPiecePtr->move(false, moveDelta, board);
        
        // promotion
        auto movedPiece = board[targetPos.x][targetPos.y];
        if (movedPiece != nullptr) {
            if (dynamic_cast<pawn*>(movedPiece.get()) != nullptr) {
                //promotion con
                if ((movedPiece->isWhite && targetPos.x == 0) || 
                    (!movedPiece->isWhite && targetPos.x == 7)) {
                    
                    //Chosing piece task default was queen
                    std::cout << "\n*** PAWN PROMOTION! ***\n";
                    std::cout << "Choose piece to promote to:\n";
                    std::cout << "Q = Queen\n";
                    std::cout << "R = Rook\n";
                    std::cout << "B = Bishop\n";
                    std::cout << "N = Knight\n";
                    std::cout << "Your choice: ";
                    
                    char promotionChoice;
                    std::cin >> promotionChoice;
                    
                    if (movedPiece->isWhite) {
                        switch(toupper(promotionChoice)) {
                            case 'Q':
                                board[targetPos.x][targetPos.y] = std::make_shared<queen>(true);
                                break;
                            case 'R':
                                board[targetPos.x][targetPos.y] = std::make_shared<rook>(true);
                                break;
                            case 'B':
                                board[targetPos.x][targetPos.y] = std::make_shared<bishop>(true);
                                break;
                            case 'N':
                                board[targetPos.x][targetPos.y] = std::make_shared<knight>(true);
                                break;
                            default:
                                board[targetPos.x][targetPos.y] = std::make_shared<queen>(true);  // Default to queen
                                std::cout << "Invalid choice. Defaulting to Queen.\n";
                                break;
                        }
                    } else {
                        switch(toupper(promotionChoice)) {
                            case 'Q':
                                board[targetPos.x][targetPos.y] = std::make_shared<queen>(false);
                                break;
                            case 'R':
                                board[targetPos.x][targetPos.y] = std::make_shared<rook>(false);
                                break;
                            case 'B':
                                board[targetPos.x][targetPos.y] = std::make_shared<bishop>(false);
                                break;
                            case 'N':
                                board[targetPos.x][targetPos.y] = std::make_shared<knight>(false);
                                break;
                            default:
                                board[targetPos.x][targetPos.y] = std::make_shared<queen>(false);  // Default to queen
                                std::cout << "Invalid choice. Defaulting to Queen.\n";
                                break;
                        }
                    }
                    //debug
                    std::cout << "Pawn promoted to " << board[targetPos.x][targetPos.y]->Sprite << "!\n";
                }
            }
        }
        
        if (wasCapture) {
            movesWithoutCapture = 0;
        } else {
            movesWithoutCapture++;
        }
        
        //summary
        std::cout << "\nMove " << turnCount << ": ";
        std::cout << ConvertToChessNotation(selectedPiece) << " -> " 
                  << ConvertToChessNotation(targetPos);
        if (wasCapture) std::cout << " (capture)";
        std::cout << "\n";
        
        whiteTurn = !whiteTurn;
        turnCount++;
        
        // Safety limit sugested by ai
        if (turnCount > 500) {
            std::cout << "\nGame too long - draw declared!\n";
            return EndCond::DRAW;
        }
        
        std::cout << "\nPress Enter to continue to next turn...";
        std::cin.ignore();
        std::cin.get();
    }
    
    return EndCond::_NULL;
}