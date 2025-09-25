#include <iostream>
#include "functions.h"
#include "tests.h"


using namespace std;


void clearConsole()
{
    #if defined(_WIN32) and defined(_WIN64)
        system("cls");
    #elif (defined(__linux__) or defined(__APPLE__))
        system("clear");
    #endif
}


void displayHnefataflLogo()
{
    cout <<R"( ___  ___  ________   _______   ________ ________  _________  ________  ________ ___          )"<<endl;
    cout <<R"(|\  \|\  \|\   ___  \|\  ___ \ |\  _____\\   __  \|\___   ___\\   __  \|\  _____\\  \        )"<<endl;
    cout <<R"(\ \  \\\  \ \  \\ \  \ \   __/|\ \  \__/\ \  \|\  \|___ \  \_\ \  \|\  \ \  \__/\ \  \        )"<<endl;
    cout <<R"( \ \   __  \ \  \\ \  \ \  \_|/_\ \   __\\ \   __  \   \ \  \ \ \   __  \ \   __\\ \  \       )"<<endl;
    cout <<R"(  \ \  \ \  \ \  \\ \  \ \  \_|\ \ \  \_| \ \  \ \  \   \ \  \ \ \  \ \  \ \  \_| \ \  \____  )"<<endl;
    cout <<R"(   \ \__\ \__\ \__\\ \__\ \_______\ \__\   \ \__\ \__\   \ \__\ \ \__\ \__\ \__\   \ \_______\)"<<endl;
    cout <<R"(    \|__|\|__|\|__| \|__|\|_______|\|__|    \|__|\|__|    \|__|  \|__|\|__|\|__|    \|_______|)"<<endl;
   cout.flush();
    cout<<endl;
}


bool chooseSizeBoard(BoardSize& aBoardSize)
{
    string result;
    cout << "Entrez la taille de plateau souhaité (11 ou 13) : ";
    cin >> result;
    if(result == "11")
    {
        aBoardSize = LITTLE;
        return true ;
    }
    else if(result == "13")
    {
        aBoardSize = BIG;
        return true;
    }
    else
    {
        return false;
    }

}


bool createBoard(Board& aBoard)
{
    BoardSize size = aBoard.itsSize;
    aBoard.itsCells = new Cell*[size];

    if(aBoard.itsCells == nullptr)
    {
        return false;
    }
    else
    {
        for(int i=0;i<size;i++)
        {
            aBoard.itsCells[i] = new Cell[size];
            if(aBoard.itsCells[i] == nullptr)
            {
                deleteBoard(aBoard);
                return false;
            }
        }
    }

    return true;
}


void deleteBoard(Board& aBoard)
{
    BoardSize size = aBoard.itsSize;
    for(int i=0;i<size;i++)
    {
        delete[] aBoard.itsCells[i];
    }

    delete[] aBoard.itsCells;

    aBoard.itsCells = nullptr;
}


void displayBoard(const Board& aBoard)
{
    BoardSize size = aBoard.itsSize;

    //affichage de la ligne de la deuxième coordonnée
    cout<<"┏━━━";
    for(int i=0;i<size;i++)
    {
        cout << "┳━━━";
    }
    cout << "┓"<<endl;


    cout << "┃   ┃ " ;
    for(int i=1;i<=size;i++)
    {
        if(i<10)
        {
            cout <<i<<" ┃ ";
        }
        else
        {
            cout <<i<<"┃ ";
        }

    }
    cout<<endl<<"┣━━━";
    for(int i=0;i<size;i++)
    {
        cout << "╋━━━";
    }
    cout << "┫"<<endl;

    for(int i=0;i<size;i++)
    {
        cout<<"┃ "<< char('A'+i)<<" ┃";
        for(int j=0;j<size;j++)
        {
            cout<<" ";
            switch(aBoard.itsCells[i][j].itsPieceType)
            {
                case SWORD:
                    cout<<"⚔";
                    break;
                case SHIELD:
                    cout<<"⛉";
                    break;
                case KING:
                    cout<<"K";
                    break;
                default:
                    switch(aBoard.itsCells[i][j].itsCellType)
                    {
                        case FORTRESS:
                            cout<<"⛫";

                            break;
                        case CASTLE:
                            cout<<"X";
                            break;

                        default:
                            cout<<" ";
                    }
            }
                cout<<" ┃";
        }
        if(i == (size-1))
        {
            cout<<endl<<"┗━━━";
            for(int i=0;i<size;i++)
            {
                cout << "┻━━━";
            }
            cout << "┛"<<endl;
        }
        else
        {
            cout<<endl<<"┣━━━";
            for(int i=0;i<size;i++)
            {
                cout << "╋━━━";
            }
            cout << "┫"<<endl;
        }


    }
}


void initializeBoard(Board& aBoard)
{
    BoardSize size = aBoard.itsSize;

    //initialisation à NONE pour les piecetype et celltype

    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            aBoard.itsCells[i][j].itsCellType = NORMAL;
            aBoard.itsCells[i][j].itsPieceType = NONE;
        }
    }

    //initialisation des piecetype SWORD
    for(int i=(size/2)-2;i<=(size/2)+2;i++)
    {
        for(int j=0;j<size;j+=size-1)
        {
            aBoard.itsCells[i][j].itsPieceType = SWORD;
        }
    }
    for(int i=0; i<size;i+=size-1)
    {
        for(int j=(size/2)-2;j<=(size/2)+2;j++)
        {
            aBoard.itsCells[i][j].itsPieceType = SWORD;
        }
    }
    aBoard.itsCells[1][size/2].itsPieceType = SWORD;
    aBoard.itsCells[size-2][size/2].itsPieceType = SWORD;
    aBoard.itsCells[size/2][1].itsPieceType = SWORD;
    aBoard.itsCells[size/2][size-2].itsPieceType = SWORD;
    //fin initialisation des piecetype SWORD

    //initialisation des piecetype SHIELD en fonction de la taille du tableau
    if(size == LITTLE)
    {
        for(int i=(size/2)-1;i<=(size/2)+1;i++)
        {
            for(int j=(size/2)-1;j<=(size/2)+1;j++)
            {
                aBoard.itsCells[i][j].itsPieceType = SHIELD;
            }
        }
        aBoard.itsCells[size/2][(size/2)-2].itsPieceType = SHIELD;
        aBoard.itsCells[size/2][(size/2)+2].itsPieceType = SHIELD;
        aBoard.itsCells[(size/2)-2][size/2].itsPieceType = SHIELD;
        aBoard.itsCells[(size/2)+2][size/2].itsPieceType = SHIELD;
    }
    else
    {
        for(int i=(size/2)-3;i<=(size/2)+3;i++)
        {
                aBoard.itsCells[i][size/2].itsPieceType = SHIELD;
        }
        for(int i=(size/2)-3;i<=(size/2)+3;i++)
        {
            aBoard.itsCells[size/2][i].itsPieceType = SHIELD;
        }

    }
    //fin initialisation des piecetype SWORD


    aBoard.itsCells[0][0].itsCellType = FORTRESS;
    aBoard.itsCells[0][size-1].itsCellType = FORTRESS;
    aBoard.itsCells[size-1][0].itsCellType = FORTRESS;
    aBoard.itsCells[size-1][size-1].itsCellType = FORTRESS;

    aBoard.itsCells[size/2][size/2].itsCellType = CASTLE;
    aBoard.itsCells[size/2][size/2].itsPieceType = KING;

}


bool isValidPosition(const Position& aPos, const Board& aBoard)
{
    BoardSize size = aBoard.itsSize;

    if(((aPos.itsCol >= 0) and (aPos.itsCol < size)) and ((aPos.itsRow >= 0) and (aPos.itsRow < size)))
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool getPositionFromInput(Position& aPosition, const Board& aBoard)
{
    string user_entry,temp="";
    int length=0, col =0;
    cin >> user_entry;

    //comptage du nombre d'élément dans l'entrée de l'utilisateur
    for(char elmt:user_entry)
    {
        length++;
    }



    //test si la longueur peute correspondre
    if((length < 2) or (length > 3))
    {
        return false;
    }

    //check si la lettre est bien comprise dans celles possible du tableau
    if((user_entry[0] >='A') and (int(user_entry[0]-'A') < char(aBoard.itsSize)))
    {
    }
    else if(user_entry[0] >='a' and (int(user_entry[0]-'a') < char(aBoard.itsSize)))
    {
        user_entry[0] +='A'-'a';
    }
    else
    {
        return false;
    }

    //test le nombre associé à la colonne
    for(int i=1;i<length;i++)
    {

        if((user_entry[i] >= '0') and (user_entry[i] <= '9'))
        {
            temp+=user_entry[i];
        }
        else
        {
            return false;
        }

    }

    col = stoi(temp);
    aPosition.itsRow = (user_entry[0]-'A');
    aPosition.itsCol = (col-1);

    if(isValidPosition(aPosition, aBoard))
    {
        return true;
    }
    else
    {
        return false;
    }

}


bool isEmptyCell(const Board& aBoard, const Position& aPos)
{
    if(aBoard.itsCells[aPos.itsRow][aPos.itsCol].itsPieceType == NONE)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool isValidMovement(const Game& aGame, const Move& aMove)
{
    int start_row = aMove.itsStartPosition.itsRow,start_col = aMove.itsStartPosition.itsCol, end_row = aMove.itsEndPosition.itsRow, end_col = aMove.itsEndPosition.itsCol;
    PlayerRole player_role = aGame.itsCurrentPlayer->itsRole;
    Position position;
    PieceType piece_type = aGame.itsBoard.itsCells[start_row][start_col].itsPieceType;

    if(isEmptyCell(aGame.itsBoard, aMove.itsStartPosition))
    {
        cerr<<"La case de départ est vide"<<endl;
        return false;
    }
    else if(!isEmptyCell(aGame.itsBoard, aMove.itsEndPosition))
    {
        cerr<<"La case d'arrivée n'est pas vide"<<endl;
        return false;
    }

    if(player_role == ATTACK)
    {
        if(aGame.itsBoard.itsCells[start_row][start_col].itsPieceType != SWORD)
        {
            cout<<"Ce pions ne vous appartient pas"<<endl;
            return false;
        }
    }
    else//implique player_role = DEFENSE
    {
        if(aGame.itsBoard.itsCells[start_row][start_col].itsPieceType == SWORD)
        {
            cout<<"Ce pions ne vous appartient pas"<<endl;
            return false;
        }
    }


    //check si il y a bien une seule coordonnée qui change
    if(((end_row - start_row) != 0) and ((end_col - start_col) != 0))
    {
        return false;
    }


    if(start_row != end_row)//test si on se dédplace verticalement
    {
        position.itsCol = start_col;
        if(start_row<end_row)
        {
            start_row++;
        }
        else
        {
            start_row--;
        }
        for(int i=min(start_row,end_row); i<=max(start_row,end_row);i++)
        {

            position.itsRow = i;
            if(!(isEmptyCell(aGame.itsBoard, position)))   //test si la case n'est pas vide
            {
                return false;
            }
            else
            {
                if(piece_type == KING)//si la pièce est un roi, alors pas besoin de verifier le type de cellule
                {
                    ;
                }
                else if(aGame.itsBoard.itsCells[i][start_col].itsCellType != NORMAL)
                {
                    return false;
                }
            }
        }
        return true;
    }
    else//sinon on se déplace horizontalement
    {
        position.itsRow = start_row;
        if(start_col<end_col)
        {
            start_col++;
        }
        else if(start_col>end_col)
        {
            start_col--;
        }

        for(int i=min(start_col,end_col); i<=max(start_col,end_col);i++)
        {
            position.itsCol = i;
            if(!(isEmptyCell(aGame.itsBoard, position)))   //test si la case n'est pas vide
            {
                return false;
            }
            else
            {
                if(piece_type == KING)//si la pièce est un roi, alors pas besoin de verifier le type de cellule
                {
                    ;
                }
                else if(aGame.itsBoard.itsCells[start_row][i].itsCellType != NORMAL)
                {
                    return false;
                }
            }
        }
        return true;
    }
}


void movePiece(Game& aGame, const Move& aMove)
{
    aGame.itsBoard.itsCells[aMove.itsEndPosition.itsRow][aMove.itsEndPosition.itsCol].itsPieceType = aGame.itsBoard.itsCells[aMove.itsStartPosition.itsRow][aMove.itsStartPosition.itsCol].itsPieceType;
    aGame.itsBoard.itsCells[aMove.itsStartPosition.itsRow][aMove.itsStartPosition.itsCol].itsPieceType = NONE;
}


void capturePieces(Game& aGame, const Move& aMove)
{
    Position end_position;
    end_position.itsRow = aMove.itsEndPosition.itsRow;
    end_position.itsCol = aMove.itsEndPosition.itsCol;

    //test de la case au dessus puis en dessous puis à gauche puis à droite
    if((end_position.itsRow-1>=0)
        and (aGame.itsBoard.itsCells[end_position.itsRow-1][end_position.itsCol].itsPieceType != NONE)
        and (aGame.itsBoard.itsCells[end_position.itsRow-1][end_position.itsCol].itsPieceType != aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol].itsPieceType))
    {
        switch(aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol].itsPieceType)
        {
        case SWORD://case d'au dessus = (shield ou king) et deux cases au dessus est dans le plateau et (sword  ou piece non normale deux cases au dessus)
            if((aGame.itsBoard.itsCells[end_position.itsRow-1][end_position.itsCol].itsPieceType == SHIELD)
                and (end_position.itsRow-2 >=0)
                and ((aGame.itsBoard.itsCells[end_position.itsRow-2][end_position.itsCol].itsPieceType == SWORD) or (aGame.itsBoard.itsCells[end_position.itsRow-2][end_position.itsCol].itsCellType != NORMAL)))
            {
                if((aGame.itsBoard.itsCells[end_position.itsRow-2][end_position.itsCol].itsCellType == CASTLE)
                    and (aGame.itsBoard.itsCells[end_position.itsRow-2][end_position.itsCol].itsPieceType == KING))
                {
                    break;
                }
                else
                {
                    aGame.itsBoard.itsCells[end_position.itsRow-1][end_position.itsCol].itsPieceType = NONE;
                }
            }
            break;
        default:
            if((aGame.itsBoard.itsCells[end_position.itsRow-1][end_position.itsCol].itsPieceType == SWORD)
                and (end_position.itsRow-2 >=0)
                and ((aGame.itsBoard.itsCells[end_position.itsRow-2][end_position.itsCol].itsPieceType == SHIELD) or (aGame.itsBoard.itsCells[end_position.itsRow-2][end_position.itsCol].itsPieceType == KING) or (aGame.itsBoard.itsCells[end_position.itsRow-2][end_position.itsCol].itsCellType != NORMAL)))
            {
                if((aGame.itsBoard.itsCells[end_position.itsRow-2][end_position.itsCol].itsCellType == CASTLE)
                    and (aGame.itsBoard.itsCells[end_position.itsRow-2][end_position.itsCol].itsPieceType == KING))
                {
                    aGame.itsBoard.itsCells[end_position.itsRow-1][end_position.itsCol].itsPieceType = NONE;
                    break;
                }
                else
                {
                    aGame.itsBoard.itsCells[end_position.itsRow-1][end_position.itsCol].itsPieceType = NONE;
                }
                break;
            }

        }
    }
    if((end_position.itsRow+1<=(aGame.itsBoard.itsSize-1))
        and (aGame.itsBoard.itsCells[end_position.itsRow+1][end_position.itsCol].itsPieceType != NONE)
        and (aGame.itsBoard.itsCells[end_position.itsRow+1][end_position.itsCol].itsPieceType != aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol].itsPieceType))
    {
        switch(aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol].itsPieceType)
        {
        case SWORD://case d'au dessus = (shield ou king) et deux cases au dessus est dans le plateau et (sword  ou piece non normale deux cases au dessus)
            if((aGame.itsBoard.itsCells[end_position.itsRow+1][end_position.itsCol].itsPieceType == SHIELD)
                and (end_position.itsRow+2 <=(aGame.itsBoard.itsSize-1))
                and ((aGame.itsBoard.itsCells[end_position.itsRow+2][end_position.itsCol].itsPieceType == SWORD) or (aGame.itsBoard.itsCells[end_position.itsRow+2][end_position.itsCol].itsCellType != NORMAL)))
            {
                if((aGame.itsBoard.itsCells[end_position.itsRow+2][end_position.itsCol].itsCellType == CASTLE)
                    and (aGame.itsBoard.itsCells[end_position.itsRow+2][end_position.itsCol].itsPieceType == KING))
                {
                    break;
                }
                else
                {
                    aGame.itsBoard.itsCells[end_position.itsRow+1][end_position.itsCol].itsPieceType = NONE;
                }
            }
            break;
        default:
            if((aGame.itsBoard.itsCells[end_position.itsRow+1][end_position.itsCol].itsPieceType == SWORD)
                and (end_position.itsRow+2 <=(aGame.itsBoard.itsSize-1))
                and ((aGame.itsBoard.itsCells[end_position.itsRow+2][end_position.itsCol].itsPieceType == SHIELD) or (aGame.itsBoard.itsCells[end_position.itsRow+2][end_position.itsCol].itsPieceType == KING) or (aGame.itsBoard.itsCells[end_position.itsRow+2][end_position.itsCol].itsCellType != NORMAL)))
            {
                if((aGame.itsBoard.itsCells[end_position.itsRow+2][end_position.itsCol].itsCellType == CASTLE)
                    and (aGame.itsBoard.itsCells[end_position.itsRow+2][end_position.itsCol].itsPieceType == KING))
                {
                    aGame.itsBoard.itsCells[end_position.itsRow+1][end_position.itsCol].itsPieceType = NONE;
                    break;
                }
                else
                {
                    aGame.itsBoard.itsCells[end_position.itsRow+1][end_position.itsCol].itsPieceType = NONE;
                }
                break;
            }

        }
    }
    if((end_position.itsCol-1>=0)
        and (aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol-1].itsPieceType != NONE)
        and (aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol-1].itsPieceType != aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol].itsPieceType))
    {
        switch(aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol].itsPieceType)
        {
        case SWORD://case d'au dessus = (shield ou king) et deux cases au dessus est dans le plateau et (sword  ou piece non normale deux cases au dessus)
            if((aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol-1].itsPieceType == SHIELD)
                and (end_position.itsCol-2 >=0)
                and ((aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol-2].itsPieceType == SWORD) or (aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol-2].itsCellType != NORMAL)))
            {
                if((aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol-2].itsCellType == CASTLE)
                    and (aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol-2].itsPieceType == KING))
                {
                    break;
                }
                else
                {
                    aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol-1].itsPieceType = NONE;
                }
            }
            break;
        default:
            if((aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol-1].itsPieceType == SWORD)
                and (end_position.itsCol-2 >=0)
                and ((aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol-2].itsPieceType == SHIELD) or (aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol-2].itsPieceType == KING) or (aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol-2].itsCellType != NORMAL)))
            {
                if((aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol-2].itsCellType == CASTLE)
                    and (aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol-2].itsPieceType == KING))
                {
                    aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol-1].itsPieceType = NONE;
                    break;
                }
                else
                {
                    aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol-1].itsPieceType = NONE;
                }
                break;
            }

        }
    }
    if((end_position.itsCol+1<=(aGame.itsBoard.itsSize-1))
        and (aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol+1].itsPieceType != NONE)
        and (aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol+1].itsPieceType != aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol].itsPieceType))
    {
        switch(aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol].itsPieceType)
        {
        case SWORD://case d'au dessus = (shield ou king) et deux cases au dessus est dans le plateau et (sword  ou piece non normale deux cases au dessus)
            if((aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol+1].itsPieceType == SHIELD)
                and (end_position.itsCol+2 <=(aGame.itsBoard.itsSize-1))
                and ((aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol+2].itsPieceType == SWORD) or (aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol+2].itsCellType != NORMAL)))
            {
                if((aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol+2].itsCellType == CASTLE)
                    and (aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol+2].itsPieceType == KING))
                {
                    break;
                }
                else
                {
                    aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol+1].itsPieceType = NONE;
                }
            }
            break;
        default:
            if((aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol+1].itsPieceType == SWORD)
                and (end_position.itsCol+2 <=(aGame.itsBoard.itsSize-1))
                and ((aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol+2].itsPieceType == SHIELD) or (aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol+2].itsPieceType == KING) or (aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol+2].itsCellType != NORMAL)))
            {
                if((aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol+2].itsCellType == CASTLE)
                    and (aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol+2].itsPieceType == KING))
                {
                    aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol+1].itsPieceType = NONE;
                    break;
                }
                else
                {
                    aGame.itsBoard.itsCells[end_position.itsRow][end_position.itsCol+1].itsPieceType = NONE;
                }
                break;
            }

        }
    }
}


void switchCurrentPlayer(Game& aGame)
{
    (aGame.itsCurrentPlayer == &aGame.itsPlayer1)? (aGame.itsCurrentPlayer = &aGame.itsPlayer2):(aGame.itsCurrentPlayer = &aGame.itsPlayer1);
}


bool isSwordLeft(const Board& aBoard)
{
    for(int i=0; i<aBoard.itsSize;i++)
    {
        for(int j=0;j<aBoard.itsSize;j++)
        {
            if(aBoard.itsCells[i][j].itsPieceType == SWORD)
            {
                return true;
            }
        }
    }
    return false;
}


Position getKingPosition(const Board& aBoard)
{
    for(int i=0; i<aBoard.itsSize;i++)
    {
        for(int j=0;j<aBoard.itsSize;j++)
        {
            if(aBoard.itsCells[i][j].itsPieceType == KING)
            {
                return {i,j};
            }
        }
    }
    return {-1,-1};
}


bool isKingEscaped(const Board& aBoard)
{
    Position position = getKingPosition(aBoard);
    if(aBoard.itsCells[position.itsRow][position.itsCol].itsCellType == FORTRESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool isKingCaptured(const Board& aBoard)
{
    Position position = getKingPosition(aBoard);
    if(position.itsRow == 0)
    {
        if((aBoard.itsCells[position.itsRow][position.itsCol-1].itsPieceType == NONE and aBoard.itsCells[position.itsRow][position.itsCol-1].itsCellType == NORMAL)
            or (aBoard.itsCells[position.itsRow][position.itsCol+1].itsPieceType == NONE and aBoard.itsCells[position.itsRow][position.itsCol+1].itsCellType == NORMAL)
            or (aBoard.itsCells[position.itsRow+1][position.itsCol].itsPieceType == NONE and aBoard.itsCells[position.itsRow+1][position.itsCol].itsCellType == NORMAL))
        {
            return false;
        }
    }
    else if(position.itsRow == aBoard.itsSize -1)
    {
        if((aBoard.itsCells[position.itsRow][position.itsCol-1].itsPieceType == NONE and aBoard.itsCells[position.itsRow][position.itsCol-1].itsCellType == NORMAL)
            or (aBoard.itsCells[position.itsRow][position.itsCol+1].itsPieceType == NONE and aBoard.itsCells[position.itsRow][position.itsCol+1].itsCellType == NORMAL)
            or (aBoard.itsCells[position.itsRow-1][position.itsCol].itsPieceType == NONE and aBoard.itsCells[position.itsRow-1][position.itsCol].itsCellType == NORMAL))
        {
            return false;
        }
    }
    else if(position.itsCol == 0)
    {
        if((aBoard.itsCells[position.itsRow-1][position.itsCol].itsPieceType == NONE and aBoard.itsCells[position.itsRow-1][position.itsCol].itsCellType == NORMAL)
            or (aBoard.itsCells[position.itsRow][position.itsCol+1].itsPieceType == NONE and aBoard.itsCells[position.itsRow][position.itsCol+1].itsCellType == NORMAL)
            or (aBoard.itsCells[position.itsRow+1][position.itsCol].itsPieceType == NONE and aBoard.itsCells[position.itsRow+1][position.itsCol].itsCellType == NORMAL))
        {
            return false;
        }
    }
    else if(position.itsCol == aBoard.itsSize -1)
    {
        if((aBoard.itsCells[position.itsRow-1][position.itsCol].itsPieceType == NONE and aBoard.itsCells[position.itsRow-1][position.itsCol].itsCellType == NORMAL)
            or (aBoard.itsCells[position.itsRow][position.itsCol-1].itsPieceType == NONE and aBoard.itsCells[position.itsRow][position.itsCol-1].itsCellType == NORMAL)
            or (aBoard.itsCells[position.itsRow+1][position.itsCol].itsPieceType == NONE and aBoard.itsCells[position.itsRow+1][position.itsCol].itsCellType == NORMAL))
        {
            return false;
        }
    }
    else
    {
        for(int i=0;i<2;i++)
        {
            if(aBoard.itsCells[position.itsRow-1+i][position.itsCol-i].itsPieceType == SWORD or aBoard.itsCells[position.itsRow-1+i][position.itsCol-i].itsCellType != NORMAL)
            {
                ;
            }
            else
            {
                return false;
            }
            if(aBoard.itsCells[position.itsRow+1-i][position.itsCol+i].itsPieceType == SWORD or aBoard.itsCells[position.itsRow+1-i][position.itsCol+i].itsCellType != NORMAL)
            {
                ;
            }
            else
            {
                return false;
            }
        }
    }

    return true;
}


bool isGameFinished(const Game& aGame)
{
    if(isKingEscaped(aGame.itsBoard))
    {
        cout<<"Le roi s'est échappé"<<endl;
        return true;
    }
    else if(!isSwordLeft(aGame.itsBoard))//! car la fonction return vrai s'il y a une épée
    {
        cout<<"Il n'y a plus d'épées sur le plateau"<<endl;
        return true;
    }
    else if(isKingCaptured(aGame.itsBoard))
    {
        cout<<"Le roi à été capturé"<<endl;
        return true;
    }

    return false;
}


Player* whoWon(const Game& aGame)
{    
    if(isKingCaptured(aGame.itsBoard) or isKingEscaped(aGame.itsBoard) or !(isSwordLeft(aGame.itsBoard)))
    {
        return aGame.itsCurrentPlayer;
    }
    else
    {
        return nullptr;
    }
}


void playGame()
{
    Game aGame;
    BoardSize aBoardSize;

    while(!menu())
    {//saisie incorrecte
    }

    playerName(aGame);

    //choix de la taille du tableau par l'utilisateur

    while(chooseSizeBoard(aBoardSize)== false)
    {
        cout<<"Saisie invalide, veuillez recommencer"<<endl;
    }


    Board aBoard;
    Position aPosition;
    Move aMove;
    bool move = false;
    char ans ='x';


    aBoard.itsSize = aBoardSize;
    createBoard(aBoard);
    initializeBoard(aBoard);

    aGame.itsBoard = aBoard;
    displayBoard(aBoard);


    while(!(isGameFinished(aGame)))
    {

        move = false;
        do
        {
            cout<<"C'est au tour de "<<aGame.itsCurrentPlayer->itsName<<" de jouer"<<endl;
            cout<<"Entrez la position de départ (A-"<<char(aGame.itsBoard.itsSize+'A'-1)<<")(1-"<<aGame.itsBoard.itsSize<<") ex A10 : ";
            if(getPositionFromInput(aPosition, aBoard))//test pour la position de départ
            {
                aMove.itsStartPosition = aPosition;
                cout<<"Entrez la position d'arrivée (A-"<<char(aGame.itsBoard.itsSize+'A'-1)<<")(1-"<<aGame.itsBoard.itsSize<<") ex A10 : ";
                if(getPositionFromInput(aPosition,aBoard))//test pour la position d'arrivée
                {
                    aMove.itsEndPosition = aPosition;
                    if(isValidMovement(aGame,aMove))
                    {
                        move = true;
                    }
                    else
                    {
                        //clearConsole();
                        displayBoard(aBoard);
                        cerr<<"Mouvement invalide"<<endl;
                    }
                }
                else
                {
                    clearConsole();
                    displayBoard(aBoard);
                    cerr<<"La case d'arrivée n'est pas valable"<<endl;
                }
            }
            else
            {
                clearConsole();
                displayBoard(aBoard);
                cerr<<"La case de départ n'est pas valide"<<endl;
            }

        }while(!move);
        movePiece(aGame,aMove);
        capturePieces(aGame,aMove);
        clearConsole();
        displayBoard(aBoard);
        switchCurrentPlayer(aGame);
    }
    switchCurrentPlayer(aGame);

    do
    {
        //clearConsole();
        displayBoard(aBoard);
        cout<<"Victoire pour "<<aGame.itsCurrentPlayer->itsName<<"."<<endl;
        cout<<"voulez vous rejouer ? (O/N) : ";
        cin>>ans;
    }while(ans != 'o' and ans != 'O' and ans != 'n' and ans != 'N');

    deleteBoard(aBoard);
    if(ans == 'o' or ans == 'O')
    {
        playGame();
    }
    else
    {
        cout<<"Fermeture du jeu";
    }

}

bool menu()
{
    clearConsole();
    displayHnefataflLogo();
    string answer;
    cout<<"     ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"<<endl;
    cout<<"     ┃                                           MENU PRINCIPAL                                           ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃Veuillez sélectionner parmis les choix suivants :                                                   ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<R"(     ┃1-Jouer au jeu : "play"                                                                             ┃)"<<endl;
    cout<<R"(     ┃2-Afficher les règles du jeu : "rules"                                                              ┃)"<<endl;
    cout<<R"(     ┃3- Quitter : "quit"                                                                                 ┃)"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"<<endl;

    cin >> answer;
    if(answer == "play")
    {
        return true;
    }
    else if(answer == "rules")
    {
        displayRules();
    }
    else if(answer == "quit")
    {
        exit(0);
    }
    return false;

}

void displayRules()
{
    clearConsole();
    cout<<"     ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"<<endl;
    cout<<"     ┃                                           REGLES DU JEU:                                           ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃ Voici les règles du hnefatafl :                                                                    ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃ Le hnefatafl est un jeu de stratégie combinatoire abstrait d'origine scandinave de la famille      ┃"<<endl;
    cout<<"     ┃ des jeux de tafl, populaire lors de l’époque viking. Il est assez fréquemment cité dans les        ┃"<<endl;
    cout<<"     ┃ sagas nordiques.                                                                                   ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃ LE PLATEAU:                                                                                        ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃   Le hnefatafl se joue à deux sur un tablier de 11 cases ou de 13 cases de côté.                   ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃ LE BUT:                                                                                            ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃   Pour le joueur avec les épées (l'attaquant), de prendre le roi adverse - Le pions au centre      ┃"<<endl;
    cout<<"     ┃   du plateau au début de la partie.                                                                ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃   Pour le joueur avec les bouclier et le roi (le défenseur), d'amener le roi dans une forteresse - ┃"<<endl;
    cout<<"     ┃   les cases dans les coins du tablier.                                                             ┃"<<endl;
    cout<<"     ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"<<endl;
    cout<<"     Veuillez appuyer sur entrée pour continuer :";
    cin.ignore();
    cin.get();
    cout<<endl;
    cout<<"     ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃ LES DEPLACEMENTS:                                                                                  ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃   Les attaquants jouent en premier.                                                                ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃   Les pionss se déplacent orthogonalement vers un emplacement libre, d'une ou plusieurs cases,     ┃"<<endl;
    cout<<"     ┃   comme la tour au jeu d'echecs.                                                                   ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃   Toutes les cases empruntées lors du déplacement doivent être libres.                             ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃   Les pions ne peuvent accéder aux quatres forteresses situés aux coins ni à la forteresse centrale┃"<<endl;
    cout<<"     ┃   où le roi commence la partie (son château)                                                       ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃ PRISE D'UN PIONS                                                                                   ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃   Un pion est battu et retiré du tablier s'il se retrouve, dans un alignement orthogonal,          ┃"<<endl;
    cout<<"     ┃   pris en tenailles par deux adversaires sur deux côtés opposés de la case qu'il occupe.           ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃   Le roi peut participer à battre un pion adverse mais on ne peut pas le battre de la même façon   ┃"<<endl;
    cout<<"     ┃   (voir plus loin).                                                                                ┃"<<endl;
    cout<<"     ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"<<endl;
    cout<<"     Veuillez appuyer sur entrée pour continuer :";
    cin.get();
    cout<<endl;
    cout<<"     ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃   Un pion est également battu s'il se retrouve pris en tenailles par un adversaire                 ┃"<<endl;
    cout<<"     ┃   et une forteresse.                                                                               ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃   Il est possible de prendre deux ou trois pions en déplaçant un seul pion.                        ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃   Un pion qui se déplace lui-même entre deux adversaires n'est pas capturé.                        ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃   La capture du roi constitue le but du jeu pour les attaquants. Pour capturer le roi, il faut     ┃"<<endl;
    cout<<"     ┃   l'entourer sur ses quatres côtés.                                                                ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃   Si le roi est sur le bord, trois pionts suffisent à le capturer.                                 ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃   il est également possible de capturer un roi qui touche sa forteresse centrale avec trois pions  ┃"<<endl;
    cout<<"     ┃   seulement.                                                                                       ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃   Un roi qui touche une forteresse de coin peut même être capturé avec deux pions seulement;       ┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┃   Pour gagner, le défenseur doit amener so nroi sur l'une des quatres forteresses situées aux coins┃"<<endl;
    cout<<"     ┃                                                                                                    ┃"<<endl;
    cout<<"     ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"<<endl;
    cout<<"     Veuillez appuyer sur entrée pour continuer :";
    cin.get();
    cout<<endl;

}

void playerName(Game& aGame)
{
    cout<<"Entrez le nom du premier joueur : ";
    cin >> aGame.itsPlayer1.itsName;
    cout<<"Entrez le nom du deuxième joueur : ";
    cin >> aGame.itsPlayer2.itsName;
    cout<<endl;
}


void playTests()
{
    test_chooseSizeBoard();
    test_createBoard();
    test_deleteBoard();
    test_initializeBoard();
    test_getPositionFromInput();
    test_isValidPosition();
    test_isEmptyCell();
    test_isValidMovement();
    test_movePiece();
    test_capturePieces();
    test_switchCurrentPlayer();
    test_isSwordLeft();
    test_getKingPosition();
    test_isKingEscaped();
    test_isKingCaptured();

}

void firstDemo()
{
    Game aGame;
    Move aMove;
    aMove.itsStartPosition = {1,10};
    aGame.itsBoard.itsSize = BIG;

    createBoard(aGame.itsBoard);

    //reinitialisation du plateau pour éviter les erreurs
    for(int i=0; i< aGame.itsBoard.itsSize;i++)
    {
        for(int j=0; j< aGame.itsBoard.itsSize; j++)
        {
            aGame.itsBoard.itsCells[i][j].itsPieceType = NONE;
        }
    }

    aGame.itsBoard.itsCells[0][9].itsPieceType = SWORD;
    aGame.itsBoard.itsCells[0][11].itsPieceType = SWORD;
    aGame.itsBoard.itsCells[4][4].itsPieceType = SWORD;
    aGame.itsBoard.itsCells[0][8].itsPieceType = SHIELD;
    aGame.itsBoard.itsCells[1][10].itsPieceType = KING;
    aGame.itsBoard.itsCells[0][12].itsCellType = FORTRESS;

    displayBoard(aGame.itsBoard);

    aGame.itsCurrentPlayer = &aGame.itsPlayer2;


    cout<<"Entrez la position d'arrivée pour le roi : (A11) ";

    if(getPositionFromInput(aMove.itsEndPosition,aGame.itsBoard))
    {
        if(isValidMovement(aGame,aMove))
        {
            movePiece(aGame,aMove);
            capturePieces(aGame,aMove);
            displayBoard(aGame.itsBoard);
        }

    }
    else
    {
        cerr<<"Erreur dans la saisie de la position, fin du programme"<<endl;
        exit(-1);
    }

    aMove.itsStartPosition = {0,10};
    cout<<"Entrez la position d'arrivée pour le roi : (A13) ";

    if(getPositionFromInput(aMove.itsEndPosition,aGame.itsBoard))
    {
        if(isValidMovement(aGame,aMove))
        {
            movePiece(aGame,aMove);
            capturePieces(aGame,aMove);
            displayBoard(aGame.itsBoard);
        }

    }
    else
    {
        cerr<<"Erreur dans la saisie de la position, fin du programme"<<endl;
        deleteBoard(aGame.itsBoard);
        exit(-1);
    }

    if(isGameFinished(aGame))
    {
        cout<<"Victoire pour le joueur "<<aGame.itsCurrentPlayer->itsRole + 1<<endl<<"Pressez la touche entrée pour passer à la deuxieme démo ";
        cin.ignore();
        cin.get();
        deleteBoard(aGame.itsBoard);
        clearConsole();
        secondDemo();
    }
    else
    {
        cout<<"Le test ne s'est pas passé comme prévu, veuillez réessayer"<<endl;
        deleteBoard(aGame.itsBoard);
        exit(-1);
    }
}

void secondDemo()
{
    Game aGame;
    Move aMove;
    aMove.itsStartPosition = {1,10};
    aGame.itsBoard.itsSize = BIG;

    createBoard(aGame.itsBoard);
    displayBoard(aGame.itsBoard);

    //reinitialisation du plateau pour éviter les erreurs
    for(int i=0; i< aGame.itsBoard.itsSize;i++)
    {
        for(int j=0; j< aGame.itsBoard.itsSize; j++)
        {
            aGame.itsBoard.itsCells[i][j].itsPieceType = NONE;
        }
    }

    aGame.itsBoard.itsCells[0][9].itsPieceType = SWORD;
    aGame.itsBoard.itsCells[0][11].itsPieceType = SWORD;
    aGame.itsBoard.itsCells[0][8].itsPieceType = SHIELD;
    aGame.itsBoard.itsCells[1][10].itsPieceType = KING;
    aGame.itsBoard.itsCells[0][12].itsCellType = FORTRESS;

    displayBoard(aGame.itsBoard);

    aGame.itsCurrentPlayer = &aGame.itsPlayer2;


    cout<<"Entrez la position d'arrivée pour le roi : (A11) ";

    if(getPositionFromInput(aMove.itsEndPosition,aGame.itsBoard))
    {
        if(isValidMovement(aGame,aMove))
        {
            movePiece(aGame,aMove);
            capturePieces(aGame,aMove);
            displayBoard(aGame.itsBoard);
        }

    }
    else
    {
        cerr<<"Erreur dans la saisie de la position, fin du programme"<<endl;
        exit(-1);
    }

    if(isGameFinished(aGame))
    {
        cout<<"Victoire pour le joueur "<<aGame.itsCurrentPlayer->itsRole + 1<<endl<<"Pressez la touche entrée pour passer à la troisème démo ";
        cin.ignore();
        cin.get();
        deleteBoard(aGame.itsBoard);
        thirdDemo();
    }
    else
    {
        cout<<"Le test ne s'est pas passé comme prévu, veuillez réessayer"<<endl;
        exit(-1);
    }
}

void thirdDemo()
{
    Game aGame;
    Move aMove;
    string answer="";
    aMove.itsStartPosition = {4,9};
    aGame.itsBoard.itsSize = LITTLE;

    createBoard(aGame.itsBoard);
    displayBoard(aGame.itsBoard);

    //reinitialisation du plateau pour éviter les erreurs
    for(int i=0; i< aGame.itsBoard.itsSize;i++)
    {
        for(int j=0; j< aGame.itsBoard.itsSize; j++)
        {
            aGame.itsBoard.itsCells[i][j].itsPieceType = NONE;
            aGame.itsBoard.itsCells[i][j].itsCellType = NORMAL;
        }
    }
    aGame.itsCurrentPlayer = &aGame.itsPlayer1;

    aGame.itsBoard.itsCells[0][8].itsPieceType = SWORD;
    aGame.itsBoard.itsCells[4][9].itsPieceType = SWORD;
    aGame.itsBoard.itsCells[0][9].itsPieceType = KING;
    aGame.itsBoard.itsCells[0][10].itsCellType = FORTRESS;

    displayBoard(aGame.itsBoard);

    cout<<"Entrez la position d'arrivée pour l'épée : (B10) ";

    if(getPositionFromInput(aMove.itsEndPosition,aGame.itsBoard))
    {
        if(isValidMovement(aGame,aMove))
        {
            movePiece(aGame,aMove);
            capturePieces(aGame,aMove);
            displayBoard(aGame.itsBoard);
        }

    }
    else
    {
        cerr<<"Erreur dans la saisie de la position, fin du programme"<<endl;
        exit(-1);
    }

    displayBoard(aGame.itsBoard);
    if(isGameFinished(aGame))
    {
        while((answer != "play") and (answer != "quit"))
        {
            clearConsole();
            displayBoard(aGame.itsBoard);
            cout<<"Victoire pour le joueur "<<aGame.itsCurrentPlayer->itsRole + 1<<endl<<R"(Fin des test, taper "play" pour jouer au jeu ou "quit" pour quitter le programme)"<<endl;
            cin>>answer;
        }

        deleteBoard(aGame.itsBoard);

        if(answer == "play")
        {
            playGame();
        }
        else if(answer == "quit")
        {
            exit(0);
        }
        else
        {
            exit(-1);
        }
    }
    else
    {
        cout<<"Le test ne s'est pas passé comme prévu, veuillez réessayer"<<endl;
        exit(-1);
    }
}
