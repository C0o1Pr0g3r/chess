#include "fen.h"
#include "checks.h"
#include "secondary functions.h"

string GetChessPieceSymbol(int piece)
{
    char symbol = ' ';
    switch (FIGURE_TYPE(piece))
    {
        case PAWN: symbol = 'p'; break;
        case KNIGHT: symbol = 'n'; break;
        case BISHOP: symbol = 'b'; break;
        case ROOK: symbol = 'r'; break;
        case QUEEN: symbol = 'q'; break;
        case KING: symbol = 'k'; break;
    }
    if (FIGURE_COLOR(piece) == WHITE)
    {
      symbol = toupper(symbol);
    }
    string result = "";
    result.push_back(symbol);

    return result;
}

string GetPiecePlacement(const int board[BOARD_SIZE][BOARD_SIZE], bool ChessboardIsInverted)
{
    string placement = "";
    const int OFFSET = 1;

    int i = OFFSET;
    int j = OFFSET;
    int emptyCellCount = 0;

    while (i < BOARD_SIZE - OFFSET && j < BOARD_SIZE - OFFSET)
    {
        string pieceSymbol = GetChessPieceSymbol(ChessboardIsInverted ? board[BOARD_SIZE - OFFSET - i][BOARD_SIZE - OFFSET - j] : board[i][j]);
        if (pieceSymbol == " ")
        {
            ++emptyCellCount;
        }
        else
        {
            if (emptyCellCount > 0)
            {
                placement.append(to_string(emptyCellCount));
                emptyCellCount = 0;
            }
            placement.append(pieceSymbol);
        }

        ++j;
        if (j == BOARD_SIZE - OFFSET)
        {
            if (emptyCellCount > 0)
            {
                placement.append(to_string(emptyCellCount));
                emptyCellCount = 0;
            }
            if (i < BOARD_SIZE - OFFSET - 1) {
                placement.append("/");
            }
            j = OFFSET;
            ++i;
        }
    }

    return placement;
}

string GetFenNotation(AppState& appState)
{
    auto& board = appState.board;
    auto& WhoseMove = appState.WhoseMove;
    auto& blackKing = appState.blackKing;
    auto& whiteKing = appState.whiteKing;
    auto& ChessboardIsInverted = appState.ChessboardIsInverted;
    auto& enPassantTargetSquare = appState.enPassantTargetSquare;
    auto& AllMovesInGame = appState.AllMovesInGame;

    int KingRookX = ChessboardIsInverted ? 1 : BOARD_SIZE - 1 - 1;
    int QueenRookX = ChessboardIsInverted ? BOARD_SIZE - 1 - 1 : 1;

    auto isPossibleWhiteKingCastling = !DKORM(appState, whiteKing.x, whiteKing.y, KingRookX, whiteKing.y);
    auto isPossibleWhiteQueenCastling = !DKORM(appState, whiteKing.x, whiteKing.y, QueenRookX, whiteKing.y);
    auto isPossibleBlackKingCastling = !DKORM(appState, blackKing.x, blackKing.y, KingRookX, blackKing.y);
    auto isPossibleBlackQueenCastling = !DKORM(appState, blackKing.x, blackKing.y, QueenRookX, blackKing.y);

    string castling = "";
    if (isPossibleWhiteKingCastling)
    {
      castling.append("K");
    }
    if (isPossibleWhiteQueenCastling)
    {
      castling.append("Q");
    }
    if (isPossibleBlackKingCastling)
    {
      castling.append("k");
    }
    if (isPossibleBlackQueenCastling)
    {
      castling.append("q");
    }

    auto fullmoveNumber = AllMovesInGame.size() < 2 ? 1 : AllMovesInGame.size() / 2 + 1;

    string SPACE = " ";
    string DASH = "-";

    string castling_str = castling.empty() ? DASH : castling;
    string enPassantTargetSquare_str = enPassantTargetSquare == Vector2i(0, 0) ? DASH : toChessNote(appState, enPassantTargetSquare);

    return GetPiecePlacement(board, ChessboardIsInverted) + SPACE + (WhoseMove ? "b" : "w") + SPACE + DASH + SPACE + DASH + SPACE + "0" + SPACE + to_string(fullmoveNumber);
}
