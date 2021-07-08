#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;


const double g = 9.81;

struct Image
{
	int mx;
	int my;
	int* points;
};

void CreateImage(Image* img, int tmx, int tmy)
{
	img->mx = tmx;
	img->my = tmy;
	img->points = new int[tmx * tmy]{ 1 };
}

void SetPointImage(Image* img, int x, int y, int collor)
{
	img->points[(y * img->mx + x)] = collor;
}

int GetPointImage(Image* img, int x, int y)
{
	return img->points[(y * img->mx + x)];

}

void ShowImage(Image* img)
{
	for (int i = 0; i < img->my; i++)
	{
		for (int j = 0; j < img->mx; j++) 	cout << img->points[i * img->mx + j] << " ";

		cout << endl;
	}
}

void SaveToPnmFile(Image* img, string fileName)
{
	fstream out;
	out.open(fileName, fstream::out);
	out << "Image" << endl;
	out << img->mx << " " << img->my << endl;

	for (int i = 0; i < img->my; i++)
	{
		for (int j = 0; j < img->mx; j++)
		{
			out << img->points[i * img->mx + j] << " ";
		}
		out << endl;
	}
	out.close();
}


struct Node
{
	double h, Vx, Vy, a, t;
	Node* next;
};

void initList(Node* head)
{
	head->h = 0;
	head->Vx = 0;
	head->Vy = 0;
	head->a = 0;
	head->t = 0;
	head->next = NULL;
}

void showList(Node* head, double h, double Vx, double Vy, double a, double t)
{
	Node* print = head;
	while (print != 0)
	{
		cout << "t= " << print->t << ", Vx = " << print->Vx << ", Vy = " << print->Vy << ", a= " << print->a << ", h= " << print->h << endl;
		print = print->next;
	}
	cout << endl;
}

void pushNode(double h, double a, double Vx, double Vy, double t)
{
	Node* nd = new Node();
	while (nd->next != NULL)
		nd = nd->next;
	nd->h = h;
	nd->Vx = Vx;
	nd->Vy = Vy;
	nd->a = a;
	nd->t = t;

	nd->next = new Node();
	initList(nd->next);
}

Node* Physics(double h, double Vx, double Vy, double dt)
{
	Node* out = new Node();

	double Vxt = Vx;
	double Vyt = Vy - g * dt;
	double V = sqrt(pow(Vxt, 2) + pow(Vyt, 2)) / 2;
	double a = pow(Vyt, 2) / (dt * dt);
	double max_t, max_h;

	if (V > 0)
	{
		max_t = V / a;
		max_h = Vyt / (2 * g);

		showList(out, h, Vxt, Vyt, g, 0);
	}
	else
	{
		showList(out, h, Vxt, Vyt, 0, 0);
	}

	double ct = dt;
	while (ct <= max_t)
	{
		h += V * ct - a * ct * ct / 2;
		Vxt = Vx;
		Vyt -= Vy - g * (dt + ct);
		showList(out, h, Vxt, Vyt, g, ct);
		ct++;
	}

	Vxt = Vx;
	Vyt = Vy - g * (ct - max_t);
	V = a * (ct - max_t);
	h = max_h - a * pow(ct - max_t, 2) / 2;
	showList(out, h, Vxt, Vyt, a, ct);
	while (ct < dt + max_t)
	{
		h -= V * ct - a * ct * ct / 2;
		Vxt = Vx;
		Vyt += Vy + g * (dt + ct);
		showList(out, h, Vxt, Vyt, g, ct);
		ct++;
	}

	showList(out, 0, 0, 0, 0, ct);
	cout << "Stop" << endl;
	return out;
}

void Interpritate(Node* lis, Image* ima)
{
	const int h_value = 10;
	const double t_value = 0.1;

	Node* current = lis;
	while (current->next != NULL)
	{
		SetPointImage(ima, t_value * current->t, (ima->my - 1) - h_value * current->h, 1);
		current = current->next;
	}
	SaveToPnmFile(ima, "modelation.pnm");
}

int main()
{
	Image* sphere = new Image;
	CreateImage(sphere, 800, 600);
	Node* list = Physics(100, 4, 6, 0.01);
	Interpritate(list, sphere);
}