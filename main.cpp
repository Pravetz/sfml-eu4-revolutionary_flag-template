#include <SFML/Graphics.hpp>
#include <iostream>


using namespace sf;

int w = 300, h = 200;
int p;
int p1;
int p2;
int save_int = 0;

int main(int argc, char** argv)
{
	using namespace std;
	
	sf::RenderWindow app(sf::VideoMode(w, h, 32), "SFML Revolutionary flag template");
	
	p = atoi(argv[1]);
	p1 = atoi(argv[2]);
	p2 = atoi(argv[3]);
	save_int = atoi(argv[4]);
	
	std::cout <<"Generate IDs: "<<p<<" "<<p1<<" "<<p2<<std::endl;
	if(p>16||p<0||p1>16||p1<0||p2>16||p2<0){
		std::cout <<"! ERROR: some IDs are invalid, therefore generation could be incorrect !"<<std::endl;
	}
	
	sf::RenderTexture texture;
	
	if (!texture.create(300, 200))
	{
		return -1;
	}
	
	Texture sector;
	
	sector.loadFromFile("assets/sectr.png");
	
	Sprite s(sector);
	Sprite s1(sector);
	Sprite s2(sector);
	
	if(p==0){
		s.setColor(sf::Color::White);	//Argent (White)
		}
	if(p==1){
		s.setColor(sf::Color(0, 0, 0, 200));	//Sable (Black)
		}
	if(p==2){
		s.setColor(sf::Color(117, 38, 143, 200));	//Purple
		}
	if(p==3){
		s.setColor(sf::Color(113, 11, 43, 200));	//Murrey (Mulberry) Burgundy
		}
	if(p==4){
		s.setColor(sf::Color(97, 12, 12, 200));	//Sanguine (Blood Red)
		}
	if(p==5){
		s.setColor(sf::Color(175, 15, 15, 200));	//Gules (Red)
		}
	if(p==6){
		s.setColor(sf::Color(188, 90, 27, 200));	//Tenné (Tawny aka orange)
		}
	if(p==7){
		s.setColor(sf::Color(64, 40, 22, 200));	//Brown
		}
	if(p==8){
		s.setColor(sf::Color(244, 184, 12, 200));	//Or (Gold)
		}
	if(p==9){
		s.setColor(sf::Color(17, 53, 13, 200));	//Dark green
		}
	if(p==10){
		s.setColor(sf::Color(46, 114, 55, 200));	//Vert (Light Green)
		}
	if(p==11){
		s.setColor(sf::Color(18, 179, 113, 200));	//Teal
		}
	if(p==12){
		s.setColor(sf::Color(50, 173, 192, 200));	//Turqouise
		}
	if(p==13){
		s.setColor(sf::Color(30, 30, 128, 200));	//Azure ( Blue)
		}
	if(p==14){
		s.setColor(sf::Color(116, 198, 240, 200));	//Bleu-Celeste (Sky Blue)
		}
	if(p==15){
		s.setColor(sf::Color(0, 68, 131, 200));	//Reflex Blue variant (darker than current french)
		}
	if(p==16){
		s.setColor(sf::Color(200, 48, 40, 200));	//Red 032 variant (darker than current french)
		}
	
	
	
	if(p1==0){
		s1.setColor(sf::Color::White);	//Argent (White)
		}
	if(p1==1){
		s1.setColor(sf::Color(0, 0, 0, 200));	//Sable (Black)
		}
	if(p1==2){
		s1.setColor(sf::Color(117, 38, 143, 200));	//Purple
		}
	if(p1==3){
		s1.setColor(sf::Color(113, 11, 43, 200));	//Murrey (Mulberry) Burgundy
		}
	if(p1==4){
		s1.setColor(sf::Color(97, 12, 12, 200));	//Sanguine (Blood Red)
		}
	if(p1==5){
		s1.setColor(sf::Color(175, 15, 15, 200));	//Gules (Red)
		}
	if(p1==6){
		s1.setColor(sf::Color(188, 90, 27, 200));	//Tenné (Tawny aka orange)
		}
	if(p1==7){
		s1.setColor(sf::Color(64, 40, 22, 200));	//Brown
		}
	if(p1==8){
		s1.setColor(sf::Color(244, 184, 12, 200));	//Or (Gold)
		}
	if(p1==9){
		s1.setColor(sf::Color(17, 53, 13, 200));	//Dark green
		}
	if(p1==10){
		s1.setColor(sf::Color(46, 114, 55, 200));	//Vert (Light Green)
		}
	if(p1==11){
		s1.setColor(sf::Color(18, 179, 113, 200));	//Teal
		}
	if(p1==12){
		s1.setColor(sf::Color(50, 173, 192, 200));	//Turqouise
		}
	if(p1==13){
		s1.setColor(sf::Color(30, 30, 128, 200));	//Azure ( Blue)
		}
	if(p1==14){
		s1.setColor(sf::Color(116, 198, 240, 200));	//Bleu-Celeste (Sky Blue)
		}
	if(p1==15){
		s1.setColor(sf::Color(0, 68, 131, 200));	//Reflex Blue variant (darker than current french)
		}
	if(p1==16){
		s1.setColor(sf::Color(200, 48, 40, 200));	//Red 032 variant (darker than current french)
		}
	
	
	
	if(p2==0){
		s2.setColor(sf::Color::White);	//Argent (White)
		}
	if(p2==1){
		s2.setColor(sf::Color(0, 0, 0, 200));	//Sable (Black)
		}
	if(p2==2){
		s2.setColor(sf::Color(117, 38, 143, 200));	//Purple
		}
	if(p2==3){
		s2.setColor(sf::Color(113, 11, 43, 200));	//Murrey (Mulberry) Burgundy
		}
	if(p2==4){
		s2.setColor(sf::Color(97, 12, 12, 200));	//Sanguine (Blood Red)
		}
	if(p2==5){
		s2.setColor(sf::Color(175, 15, 15, 200));	//Gules (Red)
		}
	if(p2==6){
		s2.setColor(sf::Color(188, 90, 27, 200));	//Tenné (Tawny aka orange)
		}
	if(p2==7){
		s2.setColor(sf::Color(64, 40, 22, 200));	//Brown
		}
	if(p2==8){
		s2.setColor(sf::Color(244, 184, 12, 200));	//Or (Gold)
		}
	if(p2==9){
		s2.setColor(sf::Color(17, 53, 13, 200));	//Dark green
		}
	if(p2==10){
		s2.setColor(sf::Color(46, 114, 55, 200));	//Vert (Light Green)
		}
	if(p2==11){
		s2.setColor(sf::Color(18, 179, 113, 200));	//Teal
		}
	if(p2==12){
		s2.setColor(sf::Color(50, 173, 192, 200));	//Turqouise
		}
	if(p2==13){
		s2.setColor(sf::Color(30, 30, 128, 200));	//Azure ( Blue)
		}
	if(p2==14){
		s2.setColor(sf::Color(116, 198, 240, 200));	//Bleu-Celeste (Sky Blue)
		}
	if(p2==15){
		s2.setColor(sf::Color(0, 68, 131, 200));	//Reflex Blue variant (darker than current french)
		}
	if(p2==16){
		s2.setColor(sf::Color(200, 48, 40, 200));	//Red 032 variant (darker than current french)
		}
	
	s.setPosition(0,0);
	s1.setPosition(100,0);
	s2.setPosition(200,0);
	
	while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                app.close();
        }
	
	
	texture.clear(sf::Color::Black);
	
	texture.draw(s);
	texture.draw(s1);
	texture.draw(s2);
	
	texture.display();
	if(save_int == 1){
		texture.getTexture().copyToImage().saveToFile("flag.png");
	}
	
	app.clear(sf::Color(220,220,220));
	
	
    Sprite sprite(texture.getTexture());
    
    app.draw(sprite);
    app.display();
        }
    
    if(save_int == 1){
		std::cout <<"|^| Saved revolutionary flag to the flag.png file."<<std::endl;
	}
    
	return 0;
}
