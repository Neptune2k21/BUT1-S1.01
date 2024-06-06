#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iomanip>

using std::string;

void afficherGrille(const std::vector<std::vector<char>>& grille, int taille) {
    std::cout << "  ";
    for (int j = 0; j < taille; ++j) {
        std::cout << char('A' + j) << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < taille; ++i) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < taille; ++j) {
            std::cout << grille[i][j] << " ";
        }
        std::cout << "\n";
    }
}

bool estVictoire(const std::vector<std::vector<char>>& grille, char joueur, int taille) {
    for (int i = 0; i < taille; ++i) {
        if (std::all_of(grille[i].begin(), grille[i].end(), [=](char c){ return c == joueur; })) return true;
        bool colonneGagnante = true;
        for (int j = 0; j < taille; ++j) {
            if (grille[j][i] != joueur) {
                colonneGagnante = false;
                break;
            }
        }
        if (colonneGagnante) return true;
    }

    bool diagonale1 = true, diagonale2 = true;
    for (int i = 0; i < taille; ++i) {
        if (grille[i][i] != joueur) diagonale1 = false;
        if (grille[i][taille - i - 1] != joueur) diagonale2 = false;
    }
    return diagonale1 || diagonale2;
}

bool estEgalite(const std::vector<std::vector<char>>& grille, int taille) {
    for (int i = 0; i < taille; ++i) {
        for (int j = 0; j < taille; ++j) {
            if (grille[i][j] == '-') return false;
        }
    }
    return true;
}

void jouerMorpionContreOrdinateur() {
    int taille;
    std::cout << "Entrez la taille de la grille (par exemple, 3 pour une grille 3x3) : ";
    std::cin >> taille;
    std::vector<std::vector<char>> grille(taille, std::vector<char>(taille, '-'));
    char joueurActuel = 'X';
    bool finJeu = false;

    std::cout << "Bienvenue au jeu du Morpion !\n";
    while (!finJeu) {
        int ligne;
        char colonne;
        afficherGrille(grille, taille);

        if (joueurActuel == 'X') {
            std::cout << "Joueur " << joueurActuel << ", entrez votre coup (ex : A 1) : ";
            std::cin >> colonne >> ligne;
            ligne--;  
            int colIndex = colonne - 'A';
            if (ligne < 0 || ligne >= taille || colIndex < 0 || colIndex >= taille || grille[ligne][colIndex] != '-') {
                std::cout << "Coup invalide, essayez à nouveau.\n";
                continue;
            } else {
                grille[ligne][colIndex] = joueurActuel;
            }
        } else {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            int colIndex;
            do {
                ligne = std::rand() % taille;
                colIndex = std::rand() % taille;
            } while (grille[ligne][colIndex] != '-');
            std::cout << "L'ordinateur joue en " << char('A' + colIndex) << " " << ligne + 1 << "\n";
            grille[ligne][colIndex] = joueurActuel;
        }

        if (estVictoire(grille, joueurActuel, taille)) {
            afficherGrille(grille, taille);
            std::cout << "Le joueur " << joueurActuel << " a gagné !\n";
            finJeu = true;
        } else if (estEgalite(grille, taille)) {
            afficherGrille(grille, taille);
            std::cout << "Match nul !\n";
            finJeu = true;
        } else {
            joueurActuel = (joueurActuel == 'X') ? 'O' : 'X';
        }
    }
}

// Les fonctions de Chi-fu-mi (Pierre-Papier-Ciseaux)
void JeuContreOrdinateur() {
    std::string joueur, ordinateur;
    int scoreJoueur = 0;
    int scoreOrdinateur = 0;
    int Essai, limite = 0;
    
    std::cout << "Combien de parties voulez-vous jouer ? : ";
    std::cin >> Essai;

    while (limite < Essai) {
        std::cout << "Choisissez Pierre, Papier ou Ciseaux (ou 'quitter' pour sortir) : ";
        std::cin >> joueur;

        if (joueur == "quitter") {
            break;
        }

        int randomNum = rand() % 3;

        if (randomNum == 0) {
            ordinateur = "pierre";
            limite++;
        } else if (randomNum == 1) {
            ordinateur = "papier";
            limite++;
        } else {
            ordinateur = "ciseaux";
            limite++;
        }

        std::cout << "L'ordinateur choisit : " << ordinateur << std::endl;

        if (joueur == ordinateur) {
            std::cout << "Match nul.\n";
        } 
        else if ((joueur == "pierre" && ordinateur == "ciseaux") ||
                   (joueur == "papier" && ordinateur == "pierre") ||
                   (joueur == "ciseaux" && ordinateur == "papier")) {
            std::cout << "Vous avez gagné !\n";
            scoreJoueur++;
        } else {
            std::cout << "Vous avez perdu.\n";
            scoreOrdinateur++;
        }

        std::cout << "Score - Vous : " << scoreJoueur << ", Ordinateur : " << scoreOrdinateur << "\n";
    }

    std::cout << "Merci d'avoir joué ! Votre score final : Vous " << scoreJoueur << " - " << scoreOrdinateur << " Ordinateur\n";
}

void JeuJoueurVsJoueur() {
    std::string joueur1, joueur2;
    int scoreJoueur1 = 0;
    int scoreJoueur2 = 0;
    int Essai, limite = 0;
    
    std::cout << "Combien de parties voulez-vous jouer ? : ";
    std::cin >> Essai;

    while (limite < Essai) {
        std::cout << "Joueur 1, choisissez Pierre, Papier ou Ciseaux (ou 'quitter' pour sortir) : ";
        std::cin >> joueur1;

        if (joueur1 == "quitter") {
            break;
        }

        std::cout << "Joueur 2, choisissez Pierre, Papier ou Ciseaux (ou 'quitter' pour sortir) : ";
        std::cin >> joueur2;

        if (joueur2 == "quitter") {
            break;
        }

        std::cout << "Joueur 1 a choisi : " << joueur1 << std::endl;
        std::cout << "Joueur 2 a choisi : " << joueur2 << std::endl;

        if (joueur1 == joueur2) {
            std::cout << "Match nul.\n";
        } 
        else if((joueur1 == "pierre" && joueur2 == "ciseaux") ||
                   (joueur1 == "papier" && joueur2 == "pierre") ||
                   (joueur1 == "ciseaux" && joueur2== "papier")) {
            std::cout << "Joueur 1 a gagné !\n";
            scoreJoueur1++;
        } else {
            std::cout << "Joueur 2 a gagné !\n";
            scoreJoueur2++;
        }

        std::cout << "Score - Joueur 1 : " << scoreJoueur1 << ", Joueur 2 : " << scoreJoueur2 << "\n";
        limite++; 
    }

    std::cout << "Merci d'avoir joué ! Score final : Joueur 1 " << scoreJoueur1 << " - " << scoreJoueur2 << " Joueur 2\n";
}

// Fonction pour afficher le menu des jeux
void afficherMenu() {
    std::cout << "\033[1;36m*******************************" << std::endl;
    std::cout << "*      Choisissez un Jeu      *" << std::endl;
    std::cout << "*******************************" << std::endl;
    std::cout << "* \033[1;33m1. Morpion contre Ordinateur \033[1;36m*" << std::endl;
    std::cout << "* \033[1;33m2. Jeu du 21                  \033[1;36m*" << std::endl;
    std::cout << "* \033[1;33m3. Chi-fu-Mi contre Ordinateur\033[1;36m*" << std::endl;
    std::cout << "* \033[1;33m4. Chi-fu-Mi Joueur contre Joueur \033[1;36m*" << std::endl;
    std::cout << "* \033[1;31m5. Quitter                     \033[1;36m*" << std::endl;
    std::cout << "*******************************" << std::endl;
    std::cout << "\033[1;36mVotre choix : \033[0m";
}

// Fonction pour le jeu du 21
/*void jouer21() {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); 
    int total = 0;
    int nombre;
    char choix;

    std::cout << "Bienvenue au jeu du 21 !\n";
    do {
        nombre = std::rand() % 10 + 1;
        std::cout << "Vous avez tiré un " << nombre << ".\n";
        total += nombre;
        std::cout << "Votre total est maintenant de " << total << ".\n";

        if (total > 21) {
            std::cout << "Vous avez dépassé 21. Vous avez perdu !\n";
            return;
        }

        std::cout << "Voulez-vous tirer un autre nombre ? (o/n) : ";
        std::cin >> choix;

    } while (choix == 'o' || choix == 'O');

    std::cout << "Vous avez terminé avec un total de " << total << ".\n";
    if (total == 21) {
        std::cout << "Félicitations ! Vous avez atteint 21 !\n";
    } else {
        std::cout << "Bonne chance la prochaine fois !\n";
    }
}*/

// Fonction principale avec le menu pour sélectionner le jeu
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int choix;

    do {
        afficherMenu();
        std::cin >> choix;

        switch (choix) {
            case 1:
                jouerMorpionContreOrdinateur();
                break;
            case 2:
                //jouer21();
                break;
            case 3:
                JeuContreOrdinateur();
                break;
            case 4:
                JeuJoueurVsJoueur();
                break;
            case 5:
                std::cout << "Merci d'avoir joué ! Au revoir !\n";
                break;
            default:
                std::cout << "Choix invalide, veuillez réessayer.\n";
                break;
        }
    } while (choix != 5);

    return 0;
}
