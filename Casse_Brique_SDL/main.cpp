#include "define.h"


int main(int argc, char* argv[])
{
    //Affichage des erreurs SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "rreur d'initialisation de la SDL: %s\n" << SDL_GetError();
    }

    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }


    //Initialisation des positions et dimensions des objets
    //Positions des briques
    const int nbBrique = WIDTH / WBRIQUE - 2;
    //Dimensions de l'écran de jeu
    cVue rendu(WIDTH, HEIGHT);
    //Position du joueur
    player joueur(WIDTH / 2 - 50, HEIGHT - 20, 100, 20);
    //Position de la balle
    balle ballePlayer(WIDTH / 2, HEIGHT / 2, 10, 10, 0, 5);

    //Initialisation de la vie du joueur 
    score game(VIE);


    //initialisation du tableau de brique
    bric tabBric[ETAGEBRIQUE][nbBrique];
    int x = WBRIQUE;
    int y = HBRIQUE;

    for (int l = 0; l < ETAGEBRIQUE; l++)
    {
        for (int c = 0; c < nbBrique - 1; c++)
        {
            tabBric[l][c].initPos(WBRIQUE, HBRIQUE, x, y);
            tabBric[l][c].setState(true);
            x += WBRIQUE + 2;
            game.addBrique();
        }
        x = WBRIQUE;
        y += HBRIQUE + 2;
    }

    //Boucle de jeu
    int close = 0;

    while (!close && !game.verifVictoire() && game.getnbLife() > 0) {
        SDL_Event event;

        //verification de la sortie de la balle
        ballePlayer.spawnBalle(&game, WIDTH, HEIGHT, &joueur);
        //deplacement de la balle   
        ballePlayer.deplacementBalle(HEIGHT);
        //verification de la colision avec le joueur
        ballePlayer.rebondJoueur(joueur.rectPosPlayer());
        //verification de la colision avec un des murs
        ballePlayer.rebondMur(WIDTH);
        //boucle de verification collisions avec les briques
        for (int l = 0; l < ETAGEBRIQUE; l++)
        {
            for (int c = 0; c < nbBrique; c++)
            {
                ballePlayer.rebondBric(&tabBric[l][c], &game);
            }

        }




        //Instruction des touches
        while (SDL_PollEvent(&event))
        {
            switch (event.type) {

            //Touche pour quitter 
            case SDL_QUIT:
                close = 1;
                break;

            //Touches pour bouger le joueur
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                //Aller à gauche (touche [<-])
                case SDLK_LEFT:
                    joueur.setPlayerState(state::left);
                    break;
                //Aller à droite (touche [->])
                case SDLK_RIGHT:
                    joueur.setPlayerState(state::right);
                    break;
                }
                break;
            //Touches lâcher par le joueur
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                case SDLK_RIGHT:
                    joueur.setPlayerState(state::idle);
                    break;
                }
                break;
            }
        }
        //Déplacement du joueur
        joueur.addPlayerPose(WIDTH - 100);




        //Affichage du terrain
        SDL_SetRenderDrawColor(rendu.getRenderer(), 0, 0, 0, 255);
        rendu.cleanRenderer();

        //affichage de la balle
        SDL_SetRenderDrawColor(rendu.getRenderer(), 255, 255, 255, 255);
        SDL_RenderFillRect(rendu.getRenderer(), &joueur.rectPosPlayer());
        SDL_RenderFillRect(rendu.getRenderer(), &ballePlayer.getRectBalle());


        for (int l = 0; l < ETAGEBRIQUE; l++)
        {
            for (int c = 0; c < nbBrique; c++)
            {
                if (tabBric[l][c].getState() == true)
                {
                    SDL_RenderFillRect(rendu.getRenderer(), &tabBric[l][c].getRect());
                }

            }

        }
        rendu.afficheRenderer();
        //60 fps
        SDL_Delay(1000 / 60);
    }

    //Affichage de "l'écran de fin"
    rendu.afficheFin(&game, WIDTH, HEIGHT);
    if (!close)
    {
        SDL_Delay(5000);
    }


    rendu.destroyRenderer();
    rendu.destroyWindow();
    return 0;
}