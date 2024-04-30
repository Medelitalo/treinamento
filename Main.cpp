#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <random>

int main()
{
    // iniciador do seed rand
    
    std::srand(static_cast<unsigned int>(std::time(nullptr))); 

    bool isgameOver = false, ganhoujogo = false;
    int NumeroAleatorio=0; 
    int delay = 400; // delay para nova sprite 
    int vida = 100; // vida inicial 
    int pontuacao = 0; // pontuação inicial 
    int min = 50, max = 400; // min e maximo para fução random dos sprites Nerds
    sf::Time elapsedTime; 
    
   

    //som do jogo
    
    sf::SoundBuffer Buffer, Fundo, ganhou; 
    sf::Sound audio1, AudioFundo, SGanhou; 

    if (!Fundo.loadFromFile("som\\fundo.mp3"))
    {
        return -1; 
    }
    AudioFundo.setBuffer(Fundo);

    if (!ganhou.loadFromFile("som\\ganhou.mp3"))
    {
        return -1; 
    }
    SGanhou.setBuffer(ganhou); 

    if (!Buffer.loadFromFile("som\\cr7.mp3"))
    {
      return -1; 
    } 
    audio1.setBuffer(Buffer); 



    //velocidade da sprite
    float Velocidade = 300.f;
    float VelocidadeN = 400.f; 

    // barra de vida
    sf::RectangleShape vidaBar(sf::Vector2f(vida, 20)); 
    vidaBar.setFillColor(sf::Color::Green); 
    vidaBar.setPosition(10, 10); 

    sf::RenderWindow window(sf::VideoMode(800, 600), "IZA OF THE GAME: FUJA DOS NERDS");

    //fonte para texto
    sf::Font font; 
    if (!font.loadFromFile("font\\Seagram tfb.ttf"))
    {
        return EXIT_FAILURE; 
    }
    //texto para a pontuação 
    sf::Text textpontuacao; 
    textpontuacao.setFont(font); 
    textpontuacao.setCharacterSize(24);
    textpontuacao.setFillColor(sf::Color::Black); 
    textpontuacao.setPosition(10.f, 30.f); 

    // Carregar a textura de img de fund
    sf::Texture Textura, nerd, Tiza, gamba; 
    if (!Textura.loadFromFile("img\\bk.jpeg"))
    {
        return 0; 
    }
    if (!nerd.loadFromFile("img\\nerd.png"))
    {
        return 0;
    }
    if (!Tiza.loadFromFile("img\\iza.jpeg"))
    {
        return 0;
    }
    if (!gamba.loadFromFile("img\\gamba.png"))
    {
        return 0;
    }
    

    //cria a sprite para a  text
    sf::Sprite Background(Textura), Pnerd(nerd), iza(Tiza), Gamba(gamba), Pnerd2(nerd);

    // Definir novass dimensoes para o sprite
    float novaAltura = Textura.getSize().x * 1.2f;
    float NovaLargura = Textura.getSize().y * 0.6f;
    Background.setScale(novaAltura / Textura.getSize().x, NovaLargura / Textura.getSize().y);

    //iza
    float novaAlturaIza = Tiza.getSize().x * 0.1f;
    float NovaLarguraIza = Tiza.getSize().y * 0.1f;
    iza.setScale(novaAlturaIza / Tiza.getSize().x, NovaLarguraIza / Tiza.getSize().y);

    //gamba
    ///float NovaAlGamba = gamba.getSize().y * 0.70f; 
    //float NovaLarGamba = gamba.getSize().x * 0.90f; 
    //Gamba.setScale(NovaAlGamba / gamba.getSize().x, NovaLarGamba / gamba.getSize().y); 

    //nerd
    float nvAltNerd = nerd.getSize().x * 0.2f; 
    float nvLgNerd = nerd.getSize().y * 0.2f; 
    Pnerd.setScale(nvAltNerd / nerd.getSize().x, nvLgNerd / nerd.getSize().y); 

    //nerd2
    float nvAltNerd2 = nerd.getSize().x * 0.2f;
    float nvLgNerd2 = nerd.getSize().y * 0.2f;
    Pnerd2.setScale(nvAltNerd2 / nerd.getSize().x, nvLgNerd2 / nerd.getSize().y);

    //define posição da sprite 
    iza.setPosition(50.f, 300.f);
    Pnerd2.setPosition(800.f, std::rand() % 500 + 1); 
    //Pnerd.setPosition(800, static_cast<float>(std::rand() % 500 + 1));

    // cria um relogio para calcular o tempo decorrido 
    sf::Clock clock; 

    AudioFundo.play();

    //loop principal
    while (window.isOpen())
    {
    

        //calcular o tempo decorrido desde o ultimo frame 
        float deltaTime = clock.restart().asSeconds();

        // geração de numeros aleatorios Pnerd 1 
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distrib(min, max);
        int randomNum1 = distrib(gen);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //mover o sprite iza 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            iza.move(-Velocidade * deltaTime, 0.f); 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            iza.move(Velocidade * deltaTime, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            iza.move(0.f, -Velocidade * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            iza.move(0.f, Velocidade * deltaTime);
        }

     
        if (Pnerd.getPosition().x <= 0)
        {
            if (pontuacao == 10)
            {
                audio1.play();
                AudioFundo.setVolume(10); 
                audio1.setVolume(100); 
            }
            Pnerd.setPosition(800, randomNum1);
            pontuacao++; 
           
            if (pontuacao % 10 == 0)
            {
                //aumentar a velocidade da sprite nerd
                VelocidadeN += 50.f;
                Velocidade += 20.f;

            }
           
        }

        if (elapsedTime.asMicroseconds() >= delay)
        {
            //se Pnerd colidir com iza, Pnerd é reposicionado para a direita
            if (Pnerd.getGlobalBounds().intersects(iza.getGlobalBounds()))
            {
                Pnerd.setPosition(800, randomNum1); 
            }
        }
        //Movimento do Pnerd
        elapsedTime = clock.getElapsedTime();
        float movimento = VelocidadeN * deltaTime;
        Pnerd.move(-movimento, 0.f);

        if (pontuacao >= 10)
        {

            if (Pnerd2.getPosition().x <= 0)
            {
                Pnerd2.setPosition(800, std::rand() % 500 + 1);

            }

            //Movimento do Pnerd2
            Pnerd2.move(-movimento, 0.f);

            if (elapsedTime.asMicroseconds() >= delay)
            {
                //se Pnerd colidir com iza, Pnerd é reposicionado para a direita
                if (Pnerd2.getGlobalBounds().intersects(iza.getGlobalBounds()))
                {
                    Pnerd2.setPosition(800, std::rand() % 500 + 1);
                }
            }
            
        }
        
        if (pontuacao >= 30)
        {
            AudioFundo.setVolume(100);
        }
       
        //atualiza o texto da pontuação 
        std::stringstream ss;
        ss << "Pontuacao: " << pontuacao;

        textpontuacao.setString(ss.str());


        //verifica colissao com a varra de vida 
        sf::FloatRect playerBounds = Pnerd.getGlobalBounds();
        sf::FloatRect vidaBounds = iza.getGlobalBounds();
       

        if (playerBounds.intersects(vidaBounds))
        {
            // se houver colissao, decremta vida 
            vida -= 20;
            int Altura = std::rand() % 500 + 1; // gera altura nova
            Pnerd.setPosition(800, static_cast<float>(Altura));
            vidaBar.setSize(sf::Vector2f(vida, 20));


            
           
           
        }
        if (vida == 40)
        {
            vidaBar.setFillColor(sf::Color::Red);

        }

        if (vida <= 10 && !isgameOver)
        {
            window.clear();
            sf::Text GameOverTxt("Game Over", font, 50);
            GameOverTxt.setPosition(300, 250);
            window.draw(GameOverTxt);
            window.display();
            

            isgameOver = true;

        }
       
        // game over
        if (isgameOver)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                {
                    vida = 100;
                    pontuacao = 0;
                    VelocidadeN = 400.f;
                    Velocidade = 300.f;
                    Pnerd.setPosition(800, std::rand() % 500 + 1);
                    Pnerd2.setPosition(800, std::rand() % 500 + 1);
                    iza.setPosition(50.f, 300.f);
                    vidaBar.setFillColor(sf::Color::Green);
                    vidaBar.setSize(sf::Vector2f(vida, 20));
                    isgameOver = false;
                    AudioFundo.stop();
                    AudioFundo.play();
                }
            } 
        }

        

      



        // LIMITAR O MOVIMENTO NA JANELA 
        sf::FloatRect spriteBounds = iza.getGlobalBounds(); 
        if (spriteBounds.left <0.f)
        {
            iza.setPosition(0.f, iza.getPosition().y);
        }
        if (spriteBounds.top < 0.f)
        {
            iza.setPosition(iza.getPosition().x, 0.f); 
        }
        if (spriteBounds.left + spriteBounds.width > window.getSize().x)
        {
            iza.setPosition(window.getSize().x - spriteBounds.width, iza.getPosition().y);
        }
        if (spriteBounds.top + spriteBounds.height > window.getSize().y) {
            iza.setPosition(iza.getPosition().x, window.getSize().y - spriteBounds.height);
        }

        if (pontuacao == 30 && !ganhoujogo)
        {
            ganhoujogo = true; 
            AudioFundo.stop();

            SGanhou.setVolume(100);

            SGanhou.play();

            window.clear();

            window.draw(Gamba);

            window.display();
        }
        if (ganhoujogo)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                {
                    vida = 100;
                    pontuacao = 0;
                    VelocidadeN = 400.f;
                    Velocidade = 300.f;
                    Pnerd.setPosition(800, std::rand() % 500 + 1);
                    Pnerd2.setPosition(800, std::rand() % 500 + 1);
                    iza.setPosition(50.f, 300.f);
                    vidaBar.setFillColor(sf::Color::Green);
                    vidaBar.setSize(sf::Vector2f(vida, 20));
                    isgameOver = false;
                    ganhoujogo = false; 
                    AudioFundo.play();
                }
            }
        }
        else
        {
            window.clear();
            window.draw(Background);
            window.draw(vidaBar);
            window.draw(textpontuacao);
            window.draw(iza);
            window.draw(Pnerd);
            window.draw(Pnerd2);
            window.display();
        }
       // window.draw(Gamba);
       
    }
   
    return 0;
}