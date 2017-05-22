// Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
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
#include "Builder.h"
#include <SFML/Graphics.hpp>

float getRedColorComponent(sf::Color c) {
	int num = c.toInteger();
	num = num >> 24 & 0xFF;
	return ((float)num) / 255;
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

void makeTreeText(std::string s, Quadtree<Photoreceptor> q) {
	std::ofstream myfile;
	myfile.open(s + ".txt");
	myfile << "Number of Retina Cells: " << q.queryRange(q.getBoundary()).size() << "\n\n";

	int counter = 0;
	for each(Data<Photoreceptor> p in q.queryRange(q.getBoundary())) {
		if (p.load->getPotential() <= p.load->getCellMin()) {
			myfile << "Cell " << ++counter << ":\n========================\n";
			myfile << "\n\tX Pos: " << p.pos.x << "\n\tY Pos: " << p.pos.y << "\n\tType: ";
			if (p.load->getType() == 'C')
				myfile << p.load->getRGB();
			myfile << p.load->getType() << "\n\tPotential: " << p.load->getPotential() << "\n\n";
		}
	}

	myfile.close();
}

int main()
{

	srand(std::time(0));
	rand();

	Quadtree<Photoreceptor> photoreceptors = photoreceptorBuilder(90000000, 6000000);
	Quadtree<Bipolar> bipolars = bipolarBuilder(photoreceptors, 14000000);
	Quadtree<Ganglion> ganglia = ganglionBuilder(bipolars, 1000000);
	//makeTreeText("Pre-Image Cells", photoreceptors);
	//photoreceptors.printTreeBoundaries();

	std::cout << "Enter name of image: ";
	std::string imageName;
	std::getline(std::cin, imageName);

	int rows = 12;
	int cols = 12;
	bool loaded = false;
	sf::Image image;
	if (!image.loadFromFile(imageName)) {
		std::cout << "\nOH SPONGEBOB, WHHYYYYYYY!!!\n\n";
		return 0;
	}

	else {
		rows = image.getSize().y;
		cols = image.getSize().x;
		loaded = true;
	}

	const int bipolarRange = 3; // I've arbitrarily made the receptive fields a 3x3 square for the purposes of this test

	//image.flipVertically();
	//image.flipHorizontally();

	std::cout << "Enter Size of Pixel (in millimeters):\n>";
	double pixelSize;
	std::cin >> pixelSize;

	Point imagePosition;
	std::cout << "Enter Image Center (in millimeters):\n X>";
	std::cin >> imagePosition.x;
	std::cout << " Y>";
	std::cin >> imagePosition.y;

	std::cout << "Enter Photons per Pixel:\n>";
	int photonsPerPixel;
	std::cin >> photonsPerPixel;

	std::cout << "Faster (y/n)?\n>";
	bool generatePhotoreceptorPics;
	char c;
	std::cin >> c;
	generatePhotoreceptorPics = c == 'y' ? true : false;

	std::vector<std::vector<Photon>> photons;
	for (int i = 0; i < rows*cols; ++i) {
		std::vector<Photon> currentRow = {};
		sf::Color c = image.getPixel(i%cols, i / cols);
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
		if (i%rows == 0)
			std::cout << "Photon Generation " << i * 100 / (rows*cols) << "% Complete\n";
	}

	std::cout << "\nPhoton Generation Complete\n";

	QuadRegion region;
	QuadRegion imageRegion(imagePosition, Point(pixelSize*image.getSize().x / 2, pixelSize*image.getSize().y / 2));

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			region = QuadRegion(Point(imagePosition.x - imageRegion.halfSize.x + (j + 0.5) * pixelSize, imagePosition.y - imageRegion.halfSize.y + (i + 0.5) * pixelSize), Point(pixelSize/2,pixelSize/2));
			for each(Data<Photoreceptor> d in photoreceptors.queryRange(region)) {
				d.load->addPhotons(photons[i*cols + j]);
				d.load->update(0);
			}
			for each(Data<Bipolar> d in bipolars.queryRange(region)) {
				d.load->update(0);
			}
			for each(Data<Ganglion> d in ganglia.queryRange(region)) {
				d.load->update(0);
			}
		}
		std::cout << "Neuron Loading " << i * 100 / rows << "% Complete\n";
	}

	std::cout << "\Neuron Loading Complete\n";

	/*std::vector<std::vector<double>> potentials;
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
	}*/

	sf::Image outputImageRods;
	outputImageRods.create(image.getSize().x, image.getSize().y, sf::Color::Black);

	sf::Image outputImageCones;
	outputImageCones.create(image.getSize().x, image.getSize().y, sf::Color::Black);

	sf::Image outputImageGanglia;
	outputImageRods.create(image.getSize().x, image.getSize().y, sf::Color::Black);

	
	std::cout << "Image Region:\n\tCentre: (" << imageRegion.centre.x << ", " << imageRegion.centre.y << ")\n";
	std::cout << "\tHalf-Size: (" << imageRegion.halfSize.x << ", " << imageRegion.halfSize.y << ")\n";

	sf::Color pixelColor;

	for (int i = 0; i < image.getSize().y; ++i) {
		for (int j = 0; j < image.getSize().x; ++j) {
			int rodCounter = 0;
			double rodPotentialSum = 0;
			int coneCounter = 0;
			double conePotentialSumRed = 0;
			double conePotentialSumGreen = 0;
			double conePotentialSumBlue = 0;
			int gCounter = 0;
			double gPotentialSum = 0;
			Rod* dummyPtrRod = new Rod();
			Cone* dummyPtrCone = new Cone(Photoreceptor::RED);
			Ganglion* dummyPtrGanglion = new Ganglion();

			region = QuadRegion(Point(imagePosition.x - imageRegion.halfSize.x + (j + 0.5) * pixelSize, imagePosition.y - imageRegion.halfSize.y + (i + 0.5) * pixelSize), Point(pixelSize / 2, pixelSize / 2));

			for each(Data<Photoreceptor> d in photoreceptors.queryRange(region)) {
				if (d.load->getType() == 'R') {
					rodCounter++;
					rodPotentialSum += d.load->getPotential();
					continue;
				}
				coneCounter++;
				switch (d.load->getRGB()) {
				case 'R':
					conePotentialSumRed += d.load->getPotential();
					break;
				case 'G':
					conePotentialSumGreen += d.load->getPotential();
					break;
				case 'B':
					conePotentialSumBlue += d.load->getPotential();
					break;
				}
			}

			if (rodCounter > 0) {
				double avgRods = ((rodPotentialSum / rodCounter) - dummyPtrRod->getCellMin()) / dummyPtrRod->getPotentialRange();
				pixelColor = sf::Color(avgRods * 255, avgRods * 255, avgRods * 255);
				outputImageRods.setPixel(j, i, pixelColor);
			}
			if (coneCounter > 0) {
				double avgRedCones = ((conePotentialSumRed / coneCounter) - dummyPtrCone->getCellMin() / dummyPtrCone->getPotentialRange());
				double avgGreenCones = ((conePotentialSumGreen / coneCounter) - dummyPtrCone->getCellMin() / dummyPtrCone->getPotentialRange());
				double avgBlueCones = ((conePotentialSumBlue / coneCounter) - dummyPtrCone->getCellMin() / dummyPtrCone->getPotentialRange());
				pixelColor = sf::Color(avgRedCones * 255, avgGreenCones * 255, avgBlueCones * 255);
				outputImageCones.setPixel(j, i, pixelColor);
			}

			for each(Data<Ganglion> d in ganglia.queryRange(region)) {
				gPotentialSum += d.load->getPotential();
				gCounter++;
			}

			if (gCounter > 0) {
				double avgGanglia = ((gPotentialSum / gCounter) - dummyPtrGanglion->getCellMin() / dummyPtrRod->getPotentialRange());
				pixelColor = sf::Color(avgGanglia * 255, avgGanglia * 255, avgGanglia * 255);
			}
		}
		std::cout << "Neuron Pixel Generation " << i * 100 / rows << "% Complete\n";
	}

	std::cout << "Neuron Pixel Generation Complete\n";

	sf::Texture gangliaOutputTexture;
	gangliaOutputTexture.loadFromImage(outputImageGanglia);
	sf::Sprite gangliaOutputSprite;
	gangliaOutputSprite.setTexture(gangliaOutputTexture);
	if (gangliaOutputTexture.getSize().x < 200)
		gangliaOutputSprite.setScale(200 / outputImageGanglia.getSize().x, 200 / outputImageGanglia.getSize().y);

	sf::Texture rodsOutputTexture;
	rodsOutputTexture.loadFromImage(outputImageRods);
	sf::Sprite rodsOutputSprite;
	rodsOutputSprite.setTexture(rodsOutputTexture);
	if (rodsOutputTexture.getSize().x < 200)
		rodsOutputSprite.setScale(200 / outputImageRods.getSize().x, 200 / outputImageRods.getSize().y);

	sf::Texture conesOutputTexture;
	conesOutputTexture.loadFromImage(outputImageCones);
	sf::Sprite conesOutputSprite;
	conesOutputSprite.setTexture(conesOutputTexture);
	if (conesOutputTexture.getSize().x < 200)
		conesOutputSprite.setScale(200 / outputImageCones.getSize().x, 200 / outputImageCones.getSize().y);

	sf::RenderWindow window(sf::VideoMode(rodsOutputSprite.getGlobalBounds().width, rodsOutputSprite.getGlobalBounds().height), "Overall");
	sf::RenderWindow window2(sf::VideoMode(rodsOutputSprite.getGlobalBounds().width, rodsOutputSprite.getGlobalBounds().height), "Rods");
	sf::RenderWindow window3(sf::VideoMode(conesOutputSprite.getGlobalBounds().width, conesOutputSprite.getGlobalBounds().height), "Cones");

	outputImageRods.saveToFile("Output/" + imageName.erase(imageName.size() - 4, imageName.size()) + "OutputRods.png");
	outputImageCones.saveToFile("Output/" + imageName + "OutputCones.png");

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

		window2.clear();
		window2.draw(rodsOutputSprite);
		window2.display();

		window3.clear();
		window3.draw(conesOutputSprite);
		window3.display();

		window.clear();
		window.draw(gangliaOutputSprite);
		window.display();
	}

	return 0;
}
