#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
const double M_PI = 3.14159265358979323846;


class button
{
	public:
	 	button()=delete;
	 	button(std::string wartosc, int x, int y, int width, int hight);
	 	void draw(sf::RenderWindow& window);
	 	bool isClicked(int x, int y);
	 	std::string getValue();
	private:
		std::string priv_value;
		int priv_x, priv_y, priv_width, priv_hight;
		sf::Font font;
		sf::Text text;
		sf::RectangleShape rectangle;
};

class solution
{
    public:
    solution(double wartosc, double okres);
    solution()=delete;
    void  display_general_solution();
    std::string get_general_solution();
    void  display_solution();
    double return_solution();
    void next();
    void preview();
    void operator++(); //preinkrementacje
    void operator--(); //predekrementacja
    void operator++(int);  //postinkrementacji
    void operator--(int); //postdekrementacja
    private:
    double x; //gÅ‚owna wartosc sinusa
    double period; //okresowosc rozwiazania
    int k; //wskazywanie rozwiazanie
};

class equation //class return solution  sin(x)=m
{
	public:
	equation()=delete;
	equation(double value); //value jest wartoscia m rozwiazywac rÃ³wnanie sin(x)=m;
	std::vector<solution> get_solves();
	private:
	std::vector<solution> wyniki; //stourage wyniki
};

void count(std::string& number, int znak, sf::Text& lResult);

int main() {

	int znak=1;
	std::string number="0";
	sf::Font font;
	font.loadFromFile("font\\Roboto.ttf"); //from google fonts
	sf::Text lDiscribe;
	lDiscribe.setFont(font);
	lDiscribe.setFillColor(sf::Color::Black);
	lDiscribe.setCharacterSize(18);
	lDiscribe.setPosition(5, 5);
	lDiscribe.setString("Rozwiazuje równanie sin(x)=m");
	sf::Text lValueM;
	lValueM.setFont(font);
	lValueM.setFillColor(sf::Color::Black);
	lValueM.setCharacterSize(18);
	lValueM.setPosition(5, 23);
	
	//inicjalizacja wygl¹du klawiatury
	std::vector<button> klawiatura;
	button keyzero("0", 85, 235, 40, 40);
	klawiatura.push_back(keyzero);
	button keyone("1", 40, 100, 40, 40);
	klawiatura.push_back(keyone);
	button keytwo("2", 85, 100, 40, 40);
	klawiatura.push_back(keytwo);
	button keythree("3", 130, 100,40, 40);
	klawiatura.push_back(keythree);
	button keyfour("4", 40, 145, 40, 40);
	klawiatura.push_back(keyfour);
	button keyfive("5", 85, 145, 40, 40);
	klawiatura.push_back(keyfive);
	button keysix("6", 130, 145, 40, 40);
	klawiatura.push_back(keysix);
	button keyseven("7", 40, 190,40, 40);
	klawiatura.push_back(keyseven);
	button keyeight("8", 85, 190, 40, 40);
	klawiatura.push_back(keyeight);
	button keynine("9", 130, 190, 40,40);
	klawiatura.push_back(keynine);
	button keydot(".",130, 235, 40, 40);
	klawiatura.push_back(keydot);
	button keycount("policz", 175, 145, 80, 40);
	klawiatura.push_back(keycount);
	button keyminus("-", 40, 235, 40,40);
	klawiatura.push_back(keyminus); 
	
	//labelka z wynikiem obliczen
	sf::Text lResult;
	lResult.setFont(font);
	lResult.setFillColor(sf::Color::Black);
	lResult.setCharacterSize(18);
	lResult.setPosition(5, 300);
    sf::RenderWindow window(sf::VideoMode(500, 400), "Test-okna", sf::Style::Titlebar | sf::Style::Close);
	
    // Ustawienie limitu na 60 klatek na sekundê
    window.setFramerateLimit(60); 

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            //ustawiæ kliekniecie cyfr na klawiaturze     
            if(event.type == sf::Event::TextEntered)
            {
            	if(event.text.unicode=='0') number=number+"0";
            	if(event.text.unicode=='1') number=number+"1";
            	if(event.text.unicode=='2') number=number+"2";
            	if(event.text.unicode=='3') number=number+"3";
            	if(event.text.unicode=='4') number=number+"4";
            	if(event.text.unicode=='5') number=number+"5";
            	if(event.text.unicode=='6') number=number+"6";
            	if(event.text.unicode=='7') number=number+"7";
            	if(event.text.unicode=='8') number=number+"8";
            	if(event.text.unicode=='9') number=number+"9";
            	if(event.text.unicode=='.') {
            		if(number.find('.')==std::string::npos) number=number+".";
				}
				if(event.text.unicode=='-')
				{
					znak=znak*(-1);
				}	
							            	
			}
			//nacisniecie shift prawy zatwierdzenie wpisywania liczby
			if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code==sf::Keyboard::RShift) 
				{
					
					count(number, znak, lResult);
				}
			}
			
			//zdarzenie naciœniêcia myszy
			if(event.type==sf::Event::MouseButtonPressed)
			{
				if(event.mouseButton.button==sf::Mouse::Left)
				{
					int m_x=event.mouseButton.x;
					int m_y=event.mouseButton.y;
					for(int i=0; i<=9; i++)
					{
						if(klawiatura[i].isClicked(m_x,m_y)) number=number+klawiatura[i].getValue();
					}
					
					if(klawiatura[10].isClicked(m_x, m_y))
					{
						if(number.find('.')==std::string::npos) number=number+".";
					}
					
					if(klawiatura[11].isClicked(m_x, m_y))
					{
						count(number, znak, lResult);
					}
					
					if(klawiatura[12].isClicked(m_x, m_y))
					{
						znak=znak*(-1);
					}
				}
			}
			
        }
        if(znak==1) lValueM.setString("m="+number);
        else lValueM.setString("m=-"+number);
        window.clear(sf::Color::Green);
        // ... rysowanie ...
		window.draw(lDiscribe);
		window.draw(lValueM);
		window.draw(lResult);
		//...rysowanie kalawiatury
		for(int i=0; i<klawiatura.size(); i++)
		{
			klawiatura[i].draw(window);
		}
		
        window.display();
    }
    return 0;
}

//definicja klasy przycisk
button::button(std::string wartosc, int x, int y, int width, int hight)
{
	this->priv_value=wartosc;
	this->priv_x=x;
	this->priv_y=y;
	this->priv_width=width;
	this->priv_hight=hight;
	
	//inicjalizacja tekstu
	this->font.loadFromFile("font\\Roboto.ttf"); 
	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color::Black);
	this->text.setPosition(5+this->priv_x, 5+this->priv_y);
	this->text.setCharacterSize(18);
	this->text.setString(this->priv_value);
	
	//inicjalizacja t³a przycisku
	this->rectangle.setSize(sf::Vector2f(this->priv_width, this->priv_hight));
	this->rectangle.setFillColor(sf::Color::Yellow);
	this->rectangle.setPosition(sf::Vector2f(this->priv_x, this->priv_y)); 
	
}

void button::draw(sf::RenderWindow& window)
{
	window.draw(this->rectangle);
	window.draw(this->text);
}

bool button::isClicked(int x, int y)
{
	if(x>=this->priv_x && x<=(this->priv_x+this->priv_width) 
	&& y>=this->priv_y && y<=(this->priv_y+this->priv_hight)) return true;
	else return false;
}

std::string button::getValue()
{
	return this->priv_value;
}


//solution
solution::solution(double wartosc, double okres)
{
    k=0;
    x=wartosc;
    period=okres;
}

void solution::display_general_solution()
{
    std::cout<<x<<"+"<<period<<"*k\n";
}

std::string solution::get_general_solution()
{
	std::string result="";
	result+=std::to_string(x);
	result+="+";
	result+=std::to_string(period);
	result+="*k";
	return result;
}

double solution::return_solution()
{
    return (x+k*period);
}

void solution::display_solution()
{
    std::cout<<(this->return_solution())<<std::endl;
}

void solution::next()
{
    k++;
}

void solution::preview()
{
    k--;
}

void solution::operator++()
{
	this->next();
}

void solution::operator--()
{
   	this->preview();
} 

void solution::operator++(int a)
{
	this->next();
}

void solution::operator--(int a)
{
	this->preview();
}

//klasy equation
std::vector<solution> equation::get_solves()
{
	return this->wyniki;
}

equation::equation(double value)
{
	if(value==1.0 || value==(-1.0))
	{
		solution x(asin(value), 2*M_PI);
		this->wyniki.push_back(x);
	}

	if(value==0.0)
	{
		solution x(asin(value), M_PI);
		this->wyniki.push_back(x);
	}
	
	if(value>0.0 && value<1.0)
	{
		 solution x_1(asin(value), 2*M_PI);
		 solution x_2((M_PI-asin(value)), 2*M_PI);
		 this->wyniki.push_back(x_1);
		 this->wyniki.push_back(x_2);
	}
	
	if(value>(-1.0) && value<0.0)
	{
		solution x_1(asin(value), 2*M_PI);
		solution x_2(((-1.0)*M_PI-asin(value)), 2*M_PI);
		this->wyniki.push_back(x_1);
		this->wyniki.push_back(x_2);
	}
		
}

//deklaracja funkcji
void count(std::string& number, int znak, sf::Text& lResult)
{
	double doubNumber=std::stod(number);
	doubNumber=doubNumber*znak;
	equation sinEquation(doubNumber);
	std::vector<solution> sinSolution=sinEquation.get_solves();
	if(sinSolution.size()==0)
	{
		lResult.setString("brak rozwiazan");
	}
	if(sinSolution.size()==1)
	{
		std::string pomString="x=";
		pomString+=sinSolution[0].get_general_solution();
		lResult.setString(pomString);
	}
	if(sinSolution.size()==2)
	{
		std::string pomString="x1=";																																																																																									
		pomString+=sinSolution[0].get_general_solution();
		pomString+="\nx2=";
		pomString+=sinSolution[1].get_general_solution();
		lResult.setString(pomString);
	}
	number="0";
}
