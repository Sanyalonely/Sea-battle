#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<random>
#include<ctime>
#include <tuple>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

const int N = 10;
int Ship_inf = 1;
int Ships[10] = { 0 };


RenderWindow window(VideoMode({ 800, 600 }), "Sea battle", State::Windowed);

class object {
public:
    Texture objectTexture;
    Sprite objectSprite;
    Vector2f objectPosition;
    Vector2f objectSize;
    bool Draw()
    {
        objectSprite.setTexture(objectTexture);
        objectSprite.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(objectTexture.getSize())));
        if (objectSize.x > 0 && objectSize.y > 0) {
            objectSprite.setScale({ objectSize.x / objectTexture.getSize().x, objectSize.y / objectTexture.getSize().y });
        }
        objectSprite.setPosition(objectPosition);
        window.draw(objectSprite);
        
        return 1;
    }
    object(void)
        : objectTexture{}
        , objectSprite(objectTexture)
        , objectPosition{}
        , objectSize{}
    {
        return;
    }
    ~object(void)
    {
        return;
    }
};

void Omniscient_general(int i, int j, int your_map[N][N]) {
    while (!(your_map[i][j] >= 1)) {
        j = rand() % N;
        i = rand() % N;
    }
    if (your_map[i][j] >= 1) {
        your_map[i][j] = -1;
    }
}

void normal_enemy_bot(int i, int j, int dir, int your_map[N][N]) {
    int miss = 0;
    j = rand() % N;
    i = rand() % N;
    i = 1;
    j = 1;
    static int hit_i, hit_j;;
    
    int first_hit_i = 0, first_hit_j = 0;

    while(miss < 1){
        
        if (your_map[i][j] >= 1) {
            your_map[i][j] = -1;
            Ships[your_map[i][j]]--;
            first_hit_i = i;
            first_hit_j = j;
            if (Ships[your_map[i][j]] != 0) {
                while (miss < 1) {
                    switch (dir) {
                    case 0: first_hit_i++; break;
                    case 1: first_hit_j++; break;
                    case 2: first_hit_i--; break;
                    case 3: first_hit_j--; break;
                    }

                    if (your_map[first_hit_i][first_hit_j] != 0 || i >= 10 || j >= 10 || i <= -1 || j <= -1) {
                        i = first_hit_i;
                        j = first_hit_j;
                        if (your_map[i][j] >= 1) {
                            your_map[i][j] = -1;
                            Ships[your_map[i][j]]--;
                            break;
                            
                        }
                        else if (your_map[i][j] == 0) {
                            your_map[i][j] = -2;
                            miss = 1;
                        }
                    }
                    
                    else {
                        first_hit_i = i;
                        first_hit_j = j;
                        dir = (dir + 1) % 4;
                    }
                }
            }
            else {
                j = rand() % N;
                i = rand() % N;
            }
        }
        else if(your_map[i][j] == -1 || your_map[i][j] == -2){
            while (your_map[i][j] == -1 || your_map[i][j] == -2) {
                j = rand() % N;
                i = rand() % N;
            }
            if (your_map[i][j] == 0) {
                your_map[i][j] = -2;
                miss++;
            }
        }
        else {
            your_map[i][j] = -2;
            miss++;
        }
    }            
}

bool ship_in_map(int x, int y, int dir, int size_ship) {

    int temp_x = x;
    int temp_y = y;
    bool in_map = true;


    for (int i = 0; i < size_ship; i++) {
        if (x < 0 || y < 0 || x >= N || y >= N) {
            in_map = false;
            break;
        }

        switch (dir) {
        case 0: x++; break;
        case 1: y++; break;
        case 2: x--; break;
        case 3: y--; break;
        }
    }
    return in_map;
}



void ship_show(int x, int y, int dir, int size_ship) {
    int selector = 1;
    object qwerty[2];

    qwerty[0].objectTexture.loadFromFile("assets/head of ship1.png");
    qwerty[1].objectTexture.loadFromFile("assets/ship deck.png");
    qwerty[0].objectSprite.setOrigin({ 17.5, 17.5 });
    qwerty[1].objectSprite.setOrigin({ 17.5, 17.5 });
    for (int i = 0; i < size_ship; i++) {
        if (i == 0) {
            selector = 0;
            switch (dir) {
            case 0: qwerty[0].objectTexture.loadFromFile("assets/head of ship1.png");
                break;
            case 1:qwerty[0].objectTexture.loadFromFile("assets/head of ship2.png");
                break;
            case 2:qwerty[0].objectTexture.loadFromFile("assets/head of ship4.png");
                break;
            case 3:qwerty[0].objectTexture.loadFromFile("assets/head of ship3.png");
                break;
            }
        }
        switch (dir) {
        case 0:  
            qwerty[selector].objectPosition = { 42.5f + y * 35.f, 142.5f + x * 35.f };
            qwerty[selector].Draw();
            x ++;
            break;
        case 1: 
            qwerty[selector].objectPosition = { 42.5f + y * 35.f, 142.5f + x * 35.f };
            if (selector != 0) {
                qwerty[selector].objectSprite.setRotation(degrees(270));
            }
            qwerty[selector].Draw();
           
            
            y ++; 
            break;
        case 2:
            qwerty[selector].objectPosition = { 42.5f + y * 35.f, 142.5f + x * 35.f };
            if (selector != 0) {
                qwerty[selector].objectSprite.setRotation(degrees(180));
            }
            qwerty[selector].Draw();
            
            x --;
            break;
        case 3: 
            qwerty[selector].objectPosition = { 42.5f + y * 35.f, 142.5f + x * 35.f };
            if (selector != 0) {
                qwerty[selector].objectSprite.setRotation(degrees(90));
            }
            qwerty[selector].Draw();
            
            y --; 
            break;
        }
        selector = 1;
    }
}

bool set_ship(int map[N][N], int x, int y, int dir, int size_ship) {
    
    int check_x = x, check_y = y;
    for (int i = 0; i < size_ship; i++) {
        if (map[check_y][check_x] != 0) {
            return false;
        }

        
        if (check_x > 0 && map[check_y][check_x - 1] != 0) return false;      
        if (check_x < N - 1 && map[check_y][check_x + 1] != 0) return false;  
        if (check_y > 0 && map[check_y - 1][check_x] != 0) return false;      
        if (check_y < N - 1 && map[check_y + 1][check_x] != 0) return false;  

        
        switch (dir) {
        case 0: check_x++; break;  
        case 1: check_y++; break;  
        case 2: check_x--; break;  
        case 3: check_y--; break; 
        }
    }

    
    for (int i = 0; i < size_ship; i++) {
        if (i == 0) {
            map[y][x] = 10 + dir;
            
        }
        else {
            map[y][x] = 6 + dir;
        }
        switch (dir) {
        case 0: x++; break;
        case 1: y++; break;
        case 2: x--; break;
        case 3: y--; break;
        }
        
    }
    Ships[Ship_inf] = size_ship;
    Ship_inf++;
    return true;
}

object map_sprite[5];

void player_map(int your_map[N][N]) {
    Vector2f Position = { 25.f, 125.f };
    object ship_head[4];
    ship_head[0].objectTexture.loadFromFile("assets/head of ship1.png");
    ship_head[1].objectTexture.loadFromFile("assets/head of ship2.png");
    ship_head[2].objectTexture.loadFromFile("assets/head of ship3.png");
    ship_head[3].objectTexture.loadFromFile("assets/head of ship4.png");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (your_map[i][j] == -1) {
                //std::cout << "X ";
                map_sprite[0].objectPosition = { Position.x + i * 35.f, Position.y + j * 35.f };
                map_sprite[0].Draw();
            }
            else if (your_map[i][j] == -2) {
                //std::cout << "O ";
                map_sprite[1].objectPosition = { Position.x + i * 35.f, Position.y + j * 35.f };
                map_sprite[1].Draw();
            }
            else if (your_map[i][j] >= 1 && your_map[i][j] <= 9) {
                //std::cout << "# ";
                switch (your_map[i][j]) {
                case 6: map_sprite[2].objectSprite.setOrigin({17.5, 17.5});
                    map_sprite[2].objectSprite.setRotation(degrees(0));
                    break;
                case 7:map_sprite[2].objectSprite.setOrigin({ 17.5, 17.5 });
                    map_sprite[2].objectSprite.setRotation(degrees(270));
                    break;
                case 8:map_sprite[2].objectSprite.setOrigin({ 17.5, 17.5 });
                    map_sprite[2].objectSprite.setRotation(degrees(180));
                    break;
                case 9:map_sprite[2].objectSprite.setOrigin({ 17.5, 17.5 });
                    map_sprite[2].objectSprite.setRotation(degrees(90));
                    break;

                }
                map_sprite[2].objectPosition = { Position.x + i * 35.f + 17.5f, Position.y + j * 35.f + 17.5f };
                map_sprite[2].Draw();
            }
            else if (your_map[i][j] >= 10 && your_map[i][j] <= 13) {
                switch (your_map[i][j]) {
                case 10:
                    ship_head[0].objectPosition = { Position.x + i * 35.f, Position.y + j * 35.f };
                    ship_head[0].Draw();
                    break;
                case 11:
                    ship_head[1].objectPosition = { Position.x + i * 35.f, Position.y + j * 35.f };
                    ship_head[1].Draw();
                    break;
                case 12:
                    ship_head[3].objectPosition = { Position.x + i * 35.f, Position.y + j * 35.f };
                    ship_head[3].Draw();
                    break;
                case 13:
                    ship_head[2].objectPosition = { Position.x + i * 35.f, Position.y + j * 35.f };
                    ship_head[2].Draw();
                    break;
                }

                
            }
            else if(your_map[i][j] == 0) {
                //std::cout << "- ";
                map_sprite[3].objectPosition = { Position.x + i * 35.f, Position.y + j * 35.f };
                map_sprite[3].Draw();
            }
        }
        std::cout << std::endl;
    }
    
}

void map_show(int map[N][N], int mask[N][N]) {
    Vector2f Position = { 425.f, 125.f };
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mask[i][j] == -1) {
                //std::cout << "X ";
                map_sprite[0].objectPosition = { Position.x + i * 35.f, Position.y + j * 35.f };
                map_sprite[0].Draw();
            }
            else if (mask[i][j] == 2) {
                //std::cout << "O ";
                map_sprite[1].objectPosition = { Position.x + i * 35.f, Position.y + j * 35.f };
                map_sprite[1].Draw();
            }
            else {
                //std::cout << "- ";
                map_sprite[3].objectPosition = { Position.x + i * 35.f, Position.y + j * 35.f };
                map_sprite[3].Draw();
            }
        }
    }
}

void set_rand_ships(int map[N][N], int size_ship, int amount_ships) {
    int x, y, dir, count_ship = 0;
    
    while (count_ship < amount_ships) {
        x = rand() % N;
        y = rand() % N;
        int temp_x = x, temp_y = y;
        bool set_possible = true;
        dir = rand() % 4;

        for (int i = 0; i < size_ship; i++) {
            if (x < 0 || y < 0 || x >= N || y >= N ||
                (map[x][y] >= 1) ||
                (y + 1 < N && map[x][y + 1] >= 1) ||
                (y - 1 >= 0 && map[x][y - 1] >= 1) ||
                (x + 1 < N && map[x + 1][y] >= 1) ||
                (x - 1 >= 0 && map[x - 1][y] >= 1)) {
                set_possible = false;
                break;
            }

            switch (dir) {
            case 0: x++; break;
            case 1: y++; break;
            case 2: x--; break;
            case 3: y--; break;
            }
        }
        
        if (set_possible) {
            x = temp_x;
            y = temp_y;
            for (int i = 0; i < size_ship; i++) {
                if (x >= 0 && x < N && y >= 0 && y < N) {
                    map[x][y] = Ship_inf;
                }
                switch (dir) {
                case 0: x++; break;
                case 1: y++; break;
                case 2: x--; break;
                case 3: y--; break;
                }
            }
            Ships[Ship_inf] = size_ship;
            Ship_inf++;
            count_ship++;
        }
        
        
    }
    Ship_inf = 1;
}

Keyboard::Scan beforeKey = Keyboard::Scan::Unknown;
bool Before = 0;

bool PressedKey(Keyboard::Scan Key, bool Reapetable)
{

    if (!isKeyPressed(beforeKey) && Before)
    {
        Before = 0;
    }
    if (isKeyPressed(Key) && !Before)
    {
        if (!Reapetable)
        {
            Before = 1;
            beforeKey = Key;
            
        }
       
        return 1;
        
    }
    return 0;
}

tuple <bool, bool> detect_ships(bool ship_Detected, bool ship_Detected_on_your_map, int mask[N][N], int map[N][N], int your_map[N][N]) {

    ship_Detected = false;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] >= 1 && mask[i][j] == 0) {
                ship_Detected = true;
                break;
            }
        }
        if (ship_Detected) break;
    }

    ship_Detected_on_your_map = false;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (your_map[i][j] >= 1) {
                ship_Detected_on_your_map = true;
                break;
            }
        }
        if (ship_Detected_on_your_map) break;
    }
    return{ ship_Detected, ship_Detected_on_your_map };
}

bool end_screen(Sprite backgroundSprite2, object End_screen) {
    object main_menu, exit;
    main_menu.objectTexture.loadFromFile("assets/exit to main menu.png");
    exit.objectTexture.loadFromFile("assets/exit before game.png");
    main_menu.objectPosition = { 300, 365 };
    exit.objectSize = { 200, 50 };
    exit.objectPosition = { 300, 425 };
    while (const optional<Event> event = window.waitEvent(10s))
    {
        if (event->is<Event::Closed>())
        {
            window.close();
        }
        if (const auto* MouseButtonReleased = event->getIf<Event::MouseButtonReleased>())
        {
            if (MouseButtonReleased->button == Mouse::Button::Left)
            {
                Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
                if (mouse.x >= 300 && mouse.x <= 500 && mouse.y >= 365 && mouse.y <= 415) {
                    return 1;
                }
                if (mouse.x >= 300 && mouse.x <= 500 && mouse.y >= 425 && mouse.y <= 475) {
                    return 0;
                }
            }
        }
        window.clear(sf::Color::Black);
        window.draw(backgroundSprite2);
        End_screen.Draw();
        main_menu.Draw();
        exit.Draw();
        window.display();
    }
    return 1;
}

void game(int map[N][N], int mask[N][N], int your_map[N][N], int count_ship, int x, int y, int dir, int size_ship) {
    int temp_x = x;
    int temp_y = y;
    int temp_dir = dir;
    int miss = 0;
    int i = 0;
    int j = 0;
    bool ship_Detected = true;
    bool ship_Detected_on_your_map = true;
    object Win_screen, Defeat_screen;
    Win_screen.objectTexture.loadFromFile("assets/victory.png");
    Win_screen.objectPosition = { 200,250 };
    Defeat_screen.objectTexture.loadFromFile("assets/defeat.png");
    Defeat_screen.objectPosition = { 200,250 };
    Texture backgroundTexture2;
    backgroundTexture2.loadFromFile("assets/background2.png");
    Sprite backgroundSprite2{ backgroundTexture2 };
    while (window.isOpen()) {
        
        
        while (const optional event = window.pollEvent()) {
            if (const auto* MouseButtonReleased = event->getIf<Event::MouseButtonReleased>())
            {
                if (MouseButtonReleased->button == Mouse::Button::Left)
                {
                    Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
                    if (miss < 2 && count_ship == 10) {

                        if (mouse.x > 425 && mouse.x < 775 && mouse.y > 125 && mouse.y < 475) {
                            int x_position;
                            int y_position;
                            mouse.x -= 425;
                            mouse.y -= 125;
                            x_position = int(mouse.x / 35);
                            y_position = int(mouse.y / 35);

                            if (map[x_position][y_position] >= 1) {
                                Ships[map[x_position][y_position]]--;
                                mask[x_position][y_position] = -1;
                                if (Ships[map[x_position][y_position]] == 0) {
                                    mask[x_position][y_position] = -1;

                                }
                                else {

                                }
                            }
                            else if (map[x_position][y_position] != 2 && map[x_position][y_position] != -1) {
                                mask[x_position][y_position] = 2;
                                miss++;

                            }
                            tie(ship_Detected, ship_Detected_on_your_map) = detect_ships(ship_Detected, ship_Detected_on_your_map, mask, map, your_map);
                            

                        }
                    }
                }
            }
            if (event->is<Event::Closed>())
            {
                
                window.close();
            }
            if(PressedKey(Keyboard::Scan::D, false)) {
                temp_y = y;
                y++;//x++;
            }
            if (PressedKey(Keyboard::Scan::S, false)) {
                temp_x = x;
                x++;//y++;
            }
            if (PressedKey(Keyboard::Scan::A, false)) {
                temp_y = y;
                y--;//x--;
            }
            if (PressedKey(Keyboard::Scan::W, false)) {
                temp_x = x;
                x--;//y--;
            }
            if (PressedKey(Keyboard::Scan::R, false)) {
                temp_dir = dir;
                dir = (dir + 1) % 4;
            }
            if (PressedKey(Keyboard::Scan::Enter, false)) {
                if (set_ship(your_map, x, y, dir, size_ship)) {
                    count_ship++;
                    // Уменьшаем розмір корабля післе установки
                    if (count_ship == 1) {
                        size_ship = 3;// Післе 1-го корабля (4 клітинки)
                    }
                    else if (count_ship == 3) {
                        size_ship = 2;// Післе 3-го (3 клітинки)
                    }
                    else if (count_ship == 6) {
                        size_ship = 1; // Післе 6-го (2 клітинки)
                    }

                }
            }

        }
        window.clear(sf::Color::Black);
        window.draw(backgroundSprite2);
        player_map(your_map);
        map_show(map, mask);
        if (count_ship <= 9) { 
            ship_show(x, y, dir, size_ship);
            if (!ship_in_map(x, y, dir, size_ship)) {
                x = temp_x;
                y = temp_y;
                dir = temp_dir;
            }
        }
        if (miss == 2) {
            Omniscient_general(i, j, your_map);
            tie(ship_Detected, ship_Detected_on_your_map) = detect_ships(ship_Detected, ship_Detected_on_your_map, mask, map, your_map);
            miss = 0;

        }
        if (!ship_Detected) {
            if (end_screen(backgroundSprite2, Win_screen)) {
                return;
            }
            else {
                window.close();
                return;
            }
        }
        else if (!ship_Detected_on_your_map) {
            if (end_screen(backgroundSprite2, Defeat_screen)) {
                return;
            }
            else {
                window.close();
                return;
            }
        }
        window.display();
    }
}

int main() {
    map_sprite[0].objectTexture.loadFromFile("assets/shooted_ship.png");
    map_sprite[1].objectTexture.loadFromFile("assets/shooted sea.png");
    map_sprite[2].objectTexture.loadFromFile("assets/ship deck.png");
    map_sprite[3].objectTexture.loadFromFile("assets/sea.png");
    map_sprite[4].objectTexture.loadFromFile("assets/head of ship1.png");
    object PlayButton, Rules_Button, Exit_Button;
    PlayButton.objectTexture.loadFromFile("assets/play.png");
    PlayButton.objectPosition = { 290,300 };
    Rules_Button.objectTexture.loadFromFile("assets/rules.png");
    Rules_Button.objectPosition = { 290,380 };
    Exit_Button.objectTexture.loadFromFile("assets/exit.png");
    Exit_Button.objectPosition = { 290,460 };
    
    Texture backgroundTexture;
    backgroundTexture.loadFromFile("assets/background1.png");
    Sprite backgroundSprite{ backgroundTexture };
    
    while (window.isOpen()) {
        srand(time(0));
        int map[N][N] = { 0 };
        int mask[N][N] = { 0 };

        set_rand_ships(map, 4, 1);
        set_rand_ships(map, 3, 2);
        set_rand_ships(map, 2, 3);
        set_rand_ships(map, 1, 4);

        int x = 0, y = 0;
        int dir = 0;
        int size_ship = 4;
        int count_ship = 0;
        int your_map[N][N] = { 0 };
        while (const optional event = window.pollEvent()) {
            if (event->is<Event::Closed>())
            {
                window.close();
            }
            if (const auto* MouseButtonReleased = event->getIf<Event::MouseButtonReleased>())
            {
                if (MouseButtonReleased->button == Mouse::Button::Left)
                {
                    Vector2f mouse = window.mapPixelToCoords(Mouse::getPosition(window));
                    if (PlayButton.objectSprite.getGlobalBounds().contains(mouse))
                    {
                        game(map, mask, your_map, count_ship, x, y, dir, size_ship);

                    }
                    if (Rules_Button.objectSprite.getGlobalBounds().contains(mouse))
                    {
                        RectangleShape Rules_screen;
                        Font Arial("assets/ARIAL.TTF");
                        Text text_of_rules(Arial);
                        text_of_rules.setCharacterSize(14);
                        text_of_rules.setFillColor(Color::Black);
                        text_of_rules.setPosition({ 201, 55 });
                        text_of_rules.setString("To exit the rules menu, press \"Esc\".\n\nAfter the game starts, place your ships in the desired\npositions using \"W\", \"A\", \"S\", \"D\", and \"R\", then press \"Enter\".\n\nOnce all ships are placed, your turn will begin.\n\nYou can make 2 moves per turn. If you hit a ship, you get one \nextra move.\n\nTo make a move, select a field and click on it with the left mouse button.");
                        Rules_screen.setFillColor({ 0, 0, 255, 200 });
                        Rules_screen.setOutlineColor(Color::Black);
                        Rules_screen.setSize({ 460, 500 });
                        Rules_screen.setOutlineThickness(10);
                        Rules_screen.setPosition({ 195, 50 });
                        while (const optional<Event> event = window.waitEvent())
                        {

                            if (event->is<Event::Closed>())
                            {
                                window.close();
                            }
                            if (PressedKey(Keyboard::Scan::Escape, false)) {
                                break;
                            }
                            window.clear(Color::Blue);
                            window.draw(backgroundSprite);
                            window.draw(Rules_screen);
                            window.draw(text_of_rules);
                            window.display();
                        }

                    }
                    if (Exit_Button.objectSprite.getGlobalBounds().contains(mouse))
                    {
                        window.close();

                    }
                }
            }

            
        }
        
        window.clear(Color::Black);
        window.draw(backgroundSprite);
        PlayButton.Draw();
        Rules_Button.Draw();
        Exit_Button.Draw();

        window.display();
 
    }
    return 0;
}