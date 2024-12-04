#include "monopoly.hpp"

Board :: Board() {
    tiles.push_back(new Property("Mumbai", "Red", 2000, 200));
    tiles.push_back(new Property("Hyderabad", "Blue", 2500, 250));
    tiles.push_back(new Property("Chennai", "Red", 2000, 200));
    tiles.push_back(new Property("Pune", "Blue", 3000, 300));
    tiles.push_back(new Property("Kolkata", "Red", 1500, 200));
    tiles.push_back(new Property("Ahmedabad", "Blue", 3500, 350));
    tiles.push_back(new Jail(500));
    tiles.push_back(new Property("Bangalore", "Red", 2000, 200));
    tiles.push_back(new Property("Jaipur", "Blue", 4000, 400));
    tiles.push_back(new Chance());
    tiles.push_back(new Property("Delhi", "Red", 2500, 300));
    tiles.push_back(new Property("Lucknow", "Blue", 4500, 450));
    tiles.push_back(new Property("Goa", "Green", 2000, 200));
    tiles.push_back(new Property("Agra", "Green", 2500, 250));
    tiles.push_back(new Property("Varanasi", "Green", 3000, 300));
    tiles.push_back(new Jail(500));
    tiles.push_back(new Property("Amritsar", "Green", 3500, 350));
    tiles.push_back(new Property("Shimla", "Green", 4000, 400));
    tiles.push_back(new IncomeTax(200, 400));
    tiles.push_back(new Property("Mysore Palace", "Yellow", 4500, 450));
    tiles.push_back(new Property("Hawa Mahal", "Yellow", 2000, 200));
    tiles.push_back(new Property("Red Fort", "Yellow", 2500, 250));
    tiles.push_back(new Chance());
    tiles.push_back(new Property("Qutub Minar", "Yellow", 3000, 300));
    tiles.push_back(new Property("Gateway of India", "Yellow", 3500, 350));
    tiles.push_back(new Jail(500));
    tiles.push_back(new Property("Charminar", "Purple", 4000, 400));
    tiles.push_back(new Property("India Gate", "Purple", 4500, 450));
    tiles.push_back(new Property("Victoria Memorial", "Purple", 2000, 200));
    tiles.push_back(new IncomeTax(200, 400));
    tiles.push_back(new Property("Lotus Temple", "Purple", 2500, 250));
    tiles.push_back(new Property("Golden Temple", "Purple", 3000, 300));
    tiles.push_back(new Chance());
    tiles.push_back(new Property("Taj Mahal", "Orange", 3500, 350));
    tiles.push_back(new Property("Sun Temple", "Orange", 4000, 400));
    tiles.push_back(new Property("Meenakshi Temple", "Orange", 4500, 450));
    tiles.push_back(new Jail(500));
    tiles.push_back(new Property("Ajanta Caves", "Orange", 2000, 200));
    tiles.push_back(new Property("Ellora Caves", "Orange", 2500, 250));
    tiles.push_back(new Chance());
}