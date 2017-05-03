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

struct BuilderData {
	float centerX;
	float centerY;
	float fovealRadius;
};

Photoreceptor* builderImage(BuilderData bd, int y, int x) {
	float r = std::sqrtf((x-bd.centerX)*(x-bd.centerX) + (y-bd.centerY)*(y-bd.centerY));

	if (r <= bd.fovealRadius) {
		if (rand() % 3 < 2)
			return new Cone(Cone::RED);
		return new Cone(Cone::GREEN);
	}
	if (r <= bd.fovealRadius * 2){
		if (rand() % 2 < 1)
			return new Rod();
		int i = rand() % 10;
		if (i < 1)
			return new Cone(Cone::BLUE);
		if (i < 4)
			return new Cone(Cone::GREEN);
		return new Cone(Cone::RED);
	}

	if (rand() % 4 < 3)
		return new Rod();
	int i = rand() % 10;
	if (i < 1)
		return new Cone(Cone::BLUE);
	if (i < 4)
		return new Cone(Cone::GREEN);
	return new Cone(Cone::RED);
	
}

Rod* builderImageTempRods(BuilderData bd, int y, int x) {
	return new Rod();

}

Cone* builderImageTempCones(BuilderData bd, int y, int x) {
	float r = std::sqrtf((x - bd.centerX)*(x - bd.centerX) + (y - bd.centerY)*(y - bd.centerY));

	if (r <= bd.fovealRadius) {
		if (rand() % 3 < 2)
			return new Cone(Cone::RED);
		return new Cone(Cone::GREEN);
	}
	int i = rand() % 10;
	if (i < 1)
		return new Cone(Cone::BLUE);
	if (i < 4)
		return new Cone(Cone::GREEN);
	return new Cone(Cone::RED);
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

sf::Image displayImageBuilder(int rows, int cols, std::vector<std::vector<Photoreceptor*>> x) {
	sf::Image displayImage;
	displayImage.create(cols, rows, sf::Color::Black);
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			sf::Color c;
			if (x[j][i]->getType() == 'R')
				c = sf::Color(64, 64, 64);		
			else {
				if (x[j][i]->getRGB() == 'B')
					c = sf::Color::Blue;
				else if (x[j][i]->getRGB() == 'G')
					c = sf::Color::Green;
				else
					c = sf::Color::Red;
			}
			displayImage.setPixel(i, j, c);
		}
	}
	return displayImage;
}

void displaySpriteInWindow(sf::Image image) {
	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite s;
	s.setTexture(texture);
	sf::RenderWindow window(sf::VideoMode(s.getGlobalBounds().width, s.getGlobalBounds().height), "Display");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(s);
		window.display();
	}
	return;
}

int main()
{
	srand(std::time(0));
	rand();

	std::cout << "Enter name of image: ";
	std::string imageName;
	std::getline(std::cin, imageName);

	int rows = 12;
	int cols = 12;
	bool loaded = false;
	sf::Image image;
	if (!image.loadFromFile(imageName + ".png")) {
		std::cout << "\nOH SPONGEBOB, WHHYYYYYYY!!!\n\n";
	}

	else {
		sf::Color c = image.getPixel(0, 0);
		std::cout << "RGBA:" << std::hex << c.toInteger() << std::dec << "\n\n";

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

	if (!loaded) {
		for (int i = 0; i < rows; ++i) {
			std::vector<Photoreceptor*> currentRow;
			for (int j = 0; j < cols; ++j) {
				currentRow.push_back(builder(i + j));
			}
			x.push_back(currentRow);
		}

		sf::Thread t(&displaySpriteInWindow, displayImageBuilder(rows, cols, x));
		t.launch();

		//Low Light
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
		std::vector<std::vector<Rod*>> rods;		
		std::vector<std::vector<Cone*>> cones;

		//image.flipVertically();

		std::cout << "Enter a foveal radius: \n>";
		
		BuilderData builderData;
		builderData.centerX = cols / 2;
		builderData.centerY = rows / 2;
		
		std::cin >> builderData.fovealRadius;

		std::cout << "Display Generation? (0 for no, 1 or higher for yes)\n>";
		int num;
		std::cin >> num;

		for (int i = 0; i < rows; ++i) {
			std::vector<Photoreceptor*> currentRow;
			for (int j = 0; j < cols; ++j) {
				currentRow.push_back(builderImageTempRods(builderData,i,j));
			}
			x.push_back(currentRow);
		}

		for (int i = 0; i < rows; ++i) {
			std::vector<Rod*> currentRow;
			for (int j = 0; j < cols; ++j) {
				currentRow.push_back(builderImageTempRods(builderData, i, j));
			}
			rods.push_back(currentRow);
		}

		for (int i = 0; i < rows; ++i) {
			std::vector<Cone*> currentRow;
			for (int j = 0; j < cols; ++j) {
				currentRow.push_back(builderImageTempCones(builderData, i, j));
			}
			cones.push_back(currentRow);
		}

		if (num != 0) {	
			sf::Thread t(&displaySpriteInWindow, displayImageBuilder(rows, cols, x));
			t.launch();
		}

		std::cout << "Enter Photons per Pixel:\n>";
		int photonsPerPixel;
		std::cin >> photonsPerPixel;
		std::vector<std::vector<Photon>> photons;
		for (int i = 0; i < rows*cols; ++i) {
			std::vector<Photon> currentRow = {};
			sf::Color c = image.getPixel(i%cols,i/cols);
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
			if(i%rows == 0)
				std::cout << "Photon Generation " << i * 100 / (rows*cols) << "% Complete\n";
		}

		std::cout << "\nPhoton Generation Complete\n";

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				x[i][j]->addPhotons(photons[i*cols + j]);
				x[i][j]->update(0);
				rods[i][j]->addPhotons(photons[i*cols + j]);
				cones[i][j]->addPhotons(photons[i*cols + j]);
				rods[i][j]->update(0);
				cones[i][j]->update(0);
			}
			std::cout << "Photoreceptor Loading " << i * 100 / rows << "% Complete\n";
		}

		std::cout << "\nPhotoreceptor Loading Complete\n";

		for (int i = 0; i < rows; i++) {
			std::vector<Bipolar*> currentRow;
			for (int j = 0; j < cols; j++) {
				currentRow.push_back(new Bipolar());
				for (int k = -(bipolarRange / 2); k < (bipolarRange / 2) + 1; k++) {
					for (int m = -(bipolarRange / 2); m < (int)(bipolarRange / 2) + 1; m++) {
						if (i + k >= 0 && i + k < rows && j + m >= 0 && j + m < cols) {
							if (m != 0 || k != 0)
								currentRow[j]->addInputCellSurround(x[i + k][j + m]);
							else
								currentRow[j]->addInputCellCenter(x[i + k][j + m]);
						}
					}
				}
			}
			y.push_back(currentRow);
			std::cout << "Bipolar Loading " << i * 100 / rows << "% Complete\n";
		}

		std::cout << "Bipolar Loading Complete\n";

		std::vector<std::vector<double>> potentials;
		for (int i = 0; i < rows; i++) {
			std::vector<double> currentRow;
			for (int j = 0; j < cols; j++) {
				y[i][j]->update(0);
				double percent = (y[i][j]->getPotential() - y[i][j]->getCellMin()) / y[i][j]->getPotentialRange();
				if (percent != 0)
					int l = 0;
				if (percent < 0) { percent *= -1; }
				currentRow.push_back(percent);
			}
			potentials.push_back(currentRow);
			std::cout << "Potential Percentages Loading " << i * 33 / rows << "% Complete\n";
		}

		std::vector<std::vector<double>> rodPotentials;
		for (int i = 0; i < rows; i++) {
			std::vector<double> currentRow;
			for (int j = 0; j < cols; j++) {
				double percent = (rods[i][j]->getPotential() - rods[i][j]->getCellMin()) / rods[i][j]->getPotentialRange();
				if (percent < 0) { percent *= -1; }
				currentRow.push_back(percent);
			}
			rodPotentials.push_back(currentRow);
			std::cout << "Potential Percentages Loading " << (i * 33 / rows + 33) << "% Complete\n";
		}

		std::vector<std::vector<double>> conePotentials;
		for (int i = 0; i < rows; i++) {
			std::vector<double> currentRow;
			for (int j = 0; j < cols; j++) {
				double percent = (cones[i][j]->getPotential() - cones[i][j]->getCellMin()) / cones[i][j]->getPotentialRange();
				if (percent < 0) { percent *= -1; }
				currentRow.push_back(percent);
			}
			conePotentials.push_back(currentRow);
			std::cout << "Potential Percentages Loading " << (i * 33 / rows + 67) << "% Complete\n";
		}

		std::cout << "Potential Percentages Complete\n";

		sf::Image outputImage;
		outputImage.create(cols,rows, sf::Color::Black);
		sf::Color pixelColor;

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				pixelColor = sf::Color(potentials[i][j]*255,potentials[i][j]*255,potentials[i][j]*255);
				outputImage.setPixel(j, i, pixelColor);
			}
		}

		std::cout << "Pixel Generation Complete\n";

		sf::Image outputImageRods;
		outputImageRods.create(cols, rows, sf::Color::Black);

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				pixelColor = sf::Color(rodPotentials[i][j] * 255, rodPotentials[i][j] * 255, rodPotentials[i][j] * 255);
				outputImageRods.setPixel(j, i, pixelColor);
			}
		}

		std::cout << "Rod Pixel Generation Complete\n";

		sf::Image outputImageCones;
		outputImageCones.create(cols, rows, sf::Color::Black);

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				switch (cones[i][j]->getRGB()) {
				case 'R':
					pixelColor = sf::Color(conePotentials[i][j] * 255,0,0);
					break;
				case 'G':
					pixelColor = sf::Color(0, conePotentials[i][j] * 255, 0);
					break;
				case 'B':
					pixelColor = sf::Color(0, 0, conePotentials[i][j] * 255);
					break;
				}
				outputImageCones.setPixel(j, i, pixelColor);
			}
		}

		std::cout << "Cone Pixel Generation Complete\n";

		sf::Texture outputTexture;
		outputTexture.loadFromImage(outputImage);
		sf::Sprite outputSprite;
		outputSprite.setTexture(outputTexture);
		if(outputTexture.getSize().x < 200)
			outputSprite.setScale(4.0f,4.0f);

		sf::Texture rodsOutputTexture;
		rodsOutputTexture.loadFromImage(outputImageRods);
		sf::Sprite rodsOutputSprite;
		rodsOutputSprite.setTexture(rodsOutputTexture);
		if (rodsOutputTexture.getSize().x < 200)
			rodsOutputSprite.setScale(4.0f, 4.0f);

		sf::Texture conesOutputTexture;
		conesOutputTexture.loadFromImage(outputImageCones);
		sf::Sprite conesOutputSprite;
		conesOutputSprite.setTexture(conesOutputTexture);
		if (conesOutputTexture.getSize().x < 200)
			conesOutputSprite.setScale(4.0f, 4.0f);

		sf::RenderWindow window(sf::VideoMode(outputSprite.getGlobalBounds().width, outputSprite.getGlobalBounds().height), "Overall");
		sf::RenderWindow window2(sf::VideoMode(rodsOutputSprite.getGlobalBounds().width, outputSprite.getGlobalBounds().height), "Rods");
		sf::RenderWindow window3(sf::VideoMode(conesOutputSprite.getGlobalBounds().width, outputSprite.getGlobalBounds().height), "Cones");

		outputImage.saveToFile("Output/" + imageName + "OutputOverall.png");
		outputImageRods.saveToFile("Output/" + imageName + "OutputOverallRods.png");
		outputImageCones.saveToFile("Output/" + imageName + "OutputOverallCones.png");

		while (window.isOpen() || window2.isOpen() || window3.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			while (window2.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window2.close();
			}
			while (window3.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window3.close();
			}

			window.clear();
			window.draw(outputSprite);
			window.display();

			window2.clear();
			window2.draw(rodsOutputSprite);
			window2.display();

			window3.clear();
			window3.draw(conesOutputSprite);
			window3.display();
		}

	}

	return 0;
}
