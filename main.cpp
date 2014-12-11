#include <iostream>
#include "tinyxml2.h"
#include <list>
#include <windows.h>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <stack>


using namespace std;
using namespace tinyxml2;
using namespace sf;
Font font;
XMLDocument doc;
XMLElement* C_element;


int main()
{
    stack<string> mi_pila;
    string fondo1= "Clima1.png";
    string fondo2= "clima2.png";
    string fondo3= "clima3.png";
    string fondo4= "Clima4.png";
    string fondo5= "clima5.png";
    string fondo6= "clima6.png";
    mi_pila.push(fondo6);
    mi_pila.push(fondo2);
    mi_pila.push(fondo3);
    mi_pila.push(fondo4);
    mi_pila.push(fondo5);
    mi_pila.push(fondo1);

    string nombre_ciudad;

    cout<<"Ingrese Ciudad"<<endl;
    getline(cin,nombre_ciudad);

    do{
            if (nombre_ciudad ==""){
                cout <<"Debe ingresar el nombre del pais "<< endl;
                cout<<"Ingrese Nombre"<<endl;
                getline(cin,nombre_ciudad);
            }
    }while(nombre_ciudad=="");

    string website ="bin\\wget.exe -nc \"http://api.openweathermap.org/data/2.5/weather?q="+nombre_ciudad+"&mode=xml\"";
    //-nc, --no-clobber no sobreescribe ficheros existentes.
    system(website.c_str());
    string ciudad = "weather@q="+nombre_ciudad+"&mode=xml";
    rename(ciudad.c_str(),nombre_ciudad.c_str());

    doc.LoadFile(nombre_ciudad.c_str());

    //NOMBRE
    C_element = doc.FirstChildElement("current")->FirstChildElement("city");
    string name =C_element->Attribute("name");

    //TEMPERATURA
     C_element = doc.FirstChildElement("current")->FirstChildElement("temperature");
     float temp = atof(C_element->Attribute("value"))-273;
     stringstream cad;
     string Temperature;
     cad << temp;
     Temperature= cad.str();

     //NUBES
     C_element = doc.FirstChildElement("current")->FirstChildElement("clouds");
     string  clouds =C_element->Attribute("name");

     //VIENTO
      C_element = doc.FirstChildElement("current")->FirstChildElement("wind")->FirstChildElement("speed");
      string  speed =C_element->Attribute("name");
      string value = C_element->Attribute("value");

      //NUBOSIDAD
     C_element = doc.FirstChildElement("current")->FirstChildElement("weather");
     string val= C_element->Attribute("value");
     //PRESSURE
      C_element = doc.FirstChildElement("current")->FirstChildElement("pressure");
     string pres= C_element->Attribute("value");
     string presunit = C_element->Attribute("unit");

     //HUMIDITY
      C_element = doc.FirstChildElement("current")->FirstChildElement("humidity");
      string humid = C_element->Attribute("value");
      string unit = C_element->Attribute("unit");
      remove(nombre_ciudad.c_str());

    RenderWindow window(VideoMode(400,250), "SFML works!");
    Texture texture;


    texture.loadFromFile(mi_pila.top());
    Sprite sprite(texture);

    Font font1;

    font1.loadFromFile("Labtop.ttf");

    Text nombre(name,font1,50);
    nombre.setPosition(180,8);
    nombre.setStyle(Text::Bold);

    Text temperature(Temperature,font1,40);
    temperature.setPosition(20,185);
    temperature.setStyle(Text::Bold);

    Text t("°C",font1,40);
    t.setPosition(70,185);
    t.setStyle(Text::Bold);

    Text clouds2(clouds,font1,35);
    clouds2.setPosition(10,150);

    //WIND
    Text wind("Wind",font1,30);
    wind.setPosition(150,110);
    wind.setStyle(Text::Bold);

    Text speed1(speed,font1,30);
    speed1.setPosition(246,110);

    Text value1(value,font1,30);
    value1.setPosition(375,110);

    //Weather
    Text weather("Cloudiness",font1,30);
    weather.setPosition(150,140);
    weather.setStyle(Text::Bold);

    Text valweather(val,font1,30);
    valweather.setPosition(246,140);
    //PRESURE
    Text Pressure("Presure",font1,30);
    Pressure.setPosition(150,170);
    Pressure.setStyle(Text::Bold);

    Text Pressval(pres,font1,30);
    Pressval.setPosition(246,170);

    Text Pressunit(presunit,font1,30);
    Pressunit.setPosition(300,170);

    //Humidity
    Text Hum("Humidity",font1,30);
    Hum.setPosition(150,200);
    Hum.setStyle(Text::Bold);

    Text HumVal(humid,font1,30);
    HumVal.setPosition(246,200);

    Text HumUnit(unit,font1,30);
    HumUnit.setPosition(270,200);

       while (window.isOpen())
        {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //FONDO
                if (event.type == sf::Event::MouseButtonReleased)
                    {
                        if(mi_pila.size()>1)
                        {
                            if(event.mouseButton.button == sf::Mouse::Left)
                            {
                                mi_pila.pop();
                                texture.loadFromFile(mi_pila.top());
                                sf::Sprite sprite1(texture);
                            }
                        }
                    }
        }
        window.clear();
        window.draw(sprite,sf::RenderStates::Default);
        window.draw(nombre);
        window.draw(temperature);
        window.draw(t);
        window.draw(clouds2);
        window.draw(wind);
        window.draw(speed1);
        window.draw(value1);
        window.draw(weather);
        window.draw(valweather);
        window.draw(Pressure);
        window.draw(Pressval);
        window.draw(Pressunit);
        window.draw(Hum);
        window.draw(HumVal);
        window.draw(HumUnit);
        window.display();
    }





   return 0;
}
