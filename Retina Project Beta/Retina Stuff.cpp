// Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include "Neuron.h"
#include "Photoreceptor.h"
#include "Cone.h"
#include "Rod.h"
#include "Bipolar.h"
#include "Ganglion.h"
#include <SFML/Graphics.hpp>

Photoreceptor* builder(int num) {
	// Method creates seqeuncial Rods and Cones depending position in the matrix
	if (num % 2 == 0) {
		Photoreceptor* p = new Rod(); // creates a new rod which is then returned
		return p;
	}
	else {
		static int count = 1; // allows for quick alteration of RGB cones being created 
		if (count % 3 == 1) {
			Photoreceptor* p = new Cone(Cone::RED);
			count++;
			return p;
		}
		else if (count % 3 == 2) {
			Photoreceptor* p = new Cone(Cone::BLUE);
			count++;
			return p;
		}
		else {
			Photoreceptor* p = new Cone(Cone::GREEN);
			count++;
			return p;
		}
	}
}

float getRedColorComponent(sf::Color c) {
	int num = c.toInteger();
	num = num >> 24 & 0xFF;
	return ((float)num)/255;
}

float getGreenColorComponent(sf::Color c) {
	int num = c.toInteger();
	num = num >> 16 & 0xFF;
	return ((float)num) / 255;
}

float getBlueColorComponent(sf::Color c) {
	int num = c.toInteger();
	num = num >> 8 & 0xFF;
	return ((float)num) / 255;
}


int main()
{
	srand(std::time(0));
	rand();

	std::cout << "Enter name of image: ";
	std::string s;
	std::getline(std::cin, s);

	int rows = 12;
	int cols = 12;
	bool loaded = false;
	sf::Image image;
	if (!image.loadFromFile(s + ".png")) {
		std::cout << "\nOH SPONGEBOB, WHHYYYYYYY!!!\n\n";
	}

	else {
		sf::Color c = image.getPixel(0, 0);
		std::cout << "RGBA:" << std::hex << c.toInteger() << "\n\n";

		rows = image.getSize().y;
		cols = image.getSize().x;
		loaded = true;
	}
	const int bipolarRange = 3; // I've arbitrarily made the receptive fields a 3x3 square for the purposes of this test


	//std::vector<Photoreceptor> receptors; // will be implemented in the future
	//std::vector<Bipolar> bipolars; 
	//std::vector<Ganglion> ganglia;


	std::vector<std::vector<Photoreceptor*>> x = {};// call a method which returns a list filled in with all the inputs;
	std::vector<std::vector<Bipolar*>> y = {};
	for (int i = 0; i < rows; ++i) {
		std::vector<Photoreceptor*> currentRow;
		for (int j = 0; j < cols; ++j) {
			currentRow.push_back(builder(i + j));
		}
		x.push_back(currentRow);
	}

	if (!loaded) {
		//Low Light
		std::cout << "Display of Rod and Cone Generator : \n\n";
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				std::cout << x[i][j]->getType();
			}
			std::cout << '\n';
		}

		std::cout << "\n\nDisplay the type of Cone that is created : \n\n";

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				std::cout << x[i][j]->getRGB();
			}
			std::cout << '\n';
		}

		std::vector<Photon> photons;
		for (int i = 0; i < 25; ++i) {
			photons.push_back(Photon());
		}
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				x[i][j]->addPhotons(photons);
				x[i][j]->update(0);
			}
		}

		for (int i = 0; i < rows / bipolarRange; i++) {
			std::vector<Bipolar*> currentRow;
			for (int j = 0; j < cols / bipolarRange; j++) {
				currentRow.push_back(new Bipolar());
				for (int k = -(bipolarRange / 2); k < (bipolarRange / 2) + 1; k++) {
					for (int m = -(bipolarRange / 2); m < (int)(bipolarRange / 2) + 1; m++) {
						if (m != 0 || k != 0)
							currentRow[j]->addInputCellSurround(x[i*bipolarRange + (bipolarRange / 2) - k][j*bipolarRange + (bipolarRange / 2) - m]);
						else
							currentRow[j]->addInputCellCenter(x[i*bipolarRange + (bipolarRange / 2) - k][j*bipolarRange + (bipolarRange / 2) - m]);
					}
				}
			}
			y.push_back(currentRow);
		}

		std::cout << "\n\nLow Light:\n\n";
		std::cout << "\nRod Potentials: \n\n";
		for (int i = 0; i < rows; ++i) {
			for (int j = i % 2; j < cols; j += 2) {
				std::cout << "[" << x[i][j]->getPotential() << "] ";
			}
			std::cout << '\n';
		}

		std::cout << "\nCone Potentials: \n\n";
		for (int i = 0; i < rows; ++i) {
			for (int j = (i + 1) % 2; j < cols; j += 2) {
				std::cout << "[" << x[i][j]->getPotential() << "] ";
			}
			std::cout << '\n';
		}

		std::cout << "\nBipolar Potentials: \n\n";
		for (int i = 0; i < rows / bipolarRange; i++) {
			for (int j = 0; j < cols / bipolarRange; j++) {
				y[i][j]->update(0);
				std::cout << "[" << y[i][j]->getPotential() << "] ";
			}
			std::cout << '\n';
		}

		//Heavy Light
		photons.clear();
		for (int i = 0; i < 200; ++i) {
			photons.push_back(Photon());
		}

		std::cout << "\n\nHeavy Light:\n\n";
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				x[i][j]->addPhotons(photons);
				x[i][j]->update(0);
			}
		}

		std::cout << "\nRod Potentials: \n\n";
		for (int i = 0; i < rows; ++i) {
			for (int j = i % 2; j < cols; j += 2) {
				std::cout << "[" << x[i][j]->getPotential() << "] ";
			}
			std::cout << '\n';
		}

		std::cout << "\nCone Potentials: \n\n";
		for (int i = 0; i < rows; ++i) {
			for (int j = (i + 1) % 2; j < cols; j += 2) {
				std::cout << "[" << x[i][j]->getPotential() << "] ";
			}
			std::cout << '\n';
		}

		std::cout << "\nBipolar Potentials: \n\n";
		for (int i = 0; i < rows / bipolarRange; i++) {
			for (int j = 0; j < cols / bipolarRange; j++) {
				y[i][j]->update(0);
				std::cout << "[" << y[i][j]->getPotential() << "] ";
			}
			std::cout << '\n';
		}
	}

	else {
		int photonsPerPixel = 25;
		std::vector<std::vector<Photon>> photons;
		for (int i = 0; i < rows*cols; ++i) {
			std::vector<Photon> currentRow = {};
			sf::Color c = image.getPixel(i/rows,i%rows);
			int red = getRedColorComponent(c) * photonsPerPixel;
			int green = getGreenColorComponent(c) * photonsPerPixel;
			int blue = getBlueColorComponent(c) * photonsPerPixel;
			for (int j = 0; j < red; ++j) {
				currentRow.push_back(Photon(650, 0));
			}
			for (int j = 0; j < green; ++j) {
				currentRow.push_back(Photon(540, 0));
			}
			for (int j = 0; j < blue; ++j) {
				currentRow.push_back(Photon(470, 0));
			}
			photons.push_back(currentRow);
		}
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				x[i][j]->addPhotons(photons[i*j]);
				x[i][j]->update(0);
			}
		}

		std::cout << "\nPhotoreceptor Loading Complete\n";

		for (int i = 0; i < rows / bipolarRange; i++) {
			std::vector<Bipolar*> currentRow;
			for (int j = 0; j < cols / bipolarRange; j++) {
				currentRow.push_back(new Bipolar());
				for (int k = -(bipolarRange / 2); k < (bipolarRange / 2) + 1; k++) {
					for (int m = -(bipolarRange / 2); m < (int)(bipolarRange / 2) + 1; m++) {
						if (m != 0 || k != 0)
							currentRow[j]->addInputCellSurround(x[i*bipolarRange + (bipolarRange / 2) - k][j*bipolarRange + (bipolarRange / 2) - m]);
						else
							currentRow[j]->addInputCellCenter(x[i*bipolarRange + (bipolarRange / 2) - k][j*bipolarRange + (bipolarRange / 2) - m]);
					}
				}
			}
			y.push_back(currentRow);
		}

		std::cout << "Bipolar Loading Complete\n";

		std::vector<std::vector<double>> potentials;
		for (int i = 0; i < rows / bipolarRange; i++) {
			std::vector<double> currentRow;
			for (int j = 0; j < cols / bipolarRange; j++) {
				y[i][j]->update(0);
				double percent = (y[i][j]->getPotential() - y[i][j]->getCellMin()) / y[i][j]->getPotentialRange();
				if (percent < 0) { percent *= -1; }
				currentRow.push_back(percent);
			}
			potentials.push_back(currentRow);
		}

		std::cout << "Potential Percentages Complete\n";

		sf::Image outputImage;
		outputImage.create(rows/bipolarRange,cols/bipolarRange, sf::Color::Black);
		sf::Color pixelColor;

		for (int i = 0; i < rows / bipolarRange; ++i) {
			for (int j = 0; j < cols / bipolarRange; ++j) {
				pixelColor = sf::Color(potentials[i][j]*255,potentials[i][j]*255,potentials[i][j]*255);
				outputImage.setPixel(i, j, pixelColor);
			}
		}

		sf::Texture outputTexture;
		outputTexture.loadFromImage(outputImage);
		sf::Sprite outputSprite;
		outputSprite.setTexture(outputTexture);
		outputSprite.setScale(12.0f,12.0f);

		sf::RenderWindow window(sf::VideoMode(rows/bipolarRange*outputSprite.getScale().x+32, cols / bipolarRange*outputSprite.getScale().y + 32), "SFML works!");

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			window.draw(outputSprite);
			window.display();
		}

	}

	return 0;
}
