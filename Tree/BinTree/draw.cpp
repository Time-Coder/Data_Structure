#ifdef BINTREE_H

template<class DataType>
template<class ElemType>
void BinTree<DataType>::circle(ofstream& file, int x0, int y0, const ElemType& label, const string& face_color, const string& font_color)
{
	file << "plt.text(" << x0 << ", " << y0
						<< ", \"" << label
						<< "\", color = \""<< font_color
						<< "\", size=15, ha=\"center\", va=\"center\", bbox=dict(boxstyle=\"circle\", ec=\"k\", fc=\""
						<< face_color << "\"))" << endl;
}

template<class DataType>
void BinTree<DataType>::connect(ofstream& file, int x1, int y1, int x2, int y2)
{
	file << "plt.plot([" << x1 << ", " << x2 << ", " << x2 << "], [" << y1 << ", " << y1 << ", " << y2 << "], 'k')" << endl;
}

template<class DataType>
void BinTree<DataType>::show(const string& title)
{
	if(empty())
	{
		cout << "The Binary Tree is empty, nothing to show!" << endl;
		return;
	}
	if (access("Figures", 0) == -1)
	{
		if(mkdir("Figures"))
		{
			cout << "Failed to make direcotory!" << endl;
			exit(-1);
		}
	}

	ofstream file("Figures/" + title + ".py");
	file << "from matplotlib.patches import Circle" << endl
		 << "import matplotlib.pyplot as plt" << endl << endl;

	int x0 = 0;
	trav_method(IN2);
	for(iterator it = begin(); it != end(); it++, x0++)
	{
		it.ptr()->x0 = x0;
		it.ptr()->y0 = -(depth(it.ptr()));
	}

	for(iterator it = begin(); it != end(); it++)
	{
		auto child = it.ptr()->lchild;
		if(child)
		{
			connect(file, it.ptr()->x0, it.ptr()->y0, child->x0, child->y0);
		}
		child = it.ptr()->rchild;
		if(child)
		{
			connect(file, it.ptr()->x0, it.ptr()->y0, child->x0, child->y0);
		}
	}

	for(iterator it = begin(); it != end(); it++)
	{
		string face_color, font_color;
		switch(it.ptr()->color)
		{
			case 0: face_color = "w"; font_color = "k"; break;
			case 1: face_color = "#282923"; font_color = "w"; break;
			case 2: face_color = "r"; font_color = "w"; break;
		}
		circle(file, it.ptr()->x0, it.ptr()->y0, *it, face_color, font_color);
	}

	file << "plt.axis('scaled')" << endl
		 <<	"plt.axis('equal')" << endl << endl
		 << "plt.axis('off')" << endl
		 << "plt.tight_layout()" << endl
		 << "fig = plt.gcf()" << endl
		 << "fig.canvas.set_window_title('" << title << "')" << endl
		 << "plt.show()" << endl;

	file.close();
	system(("start python \"Figures/" + title + ".py\"").data());
}

template<class DataType>
void BinTree<DataType>::show_content(const string& title)
{
	if(empty())
	{
		cout << "The Binary Tree is empty, nothing to show!" << endl;
		return;
	}

	ofstream file("Figures/" + title + ".py");
	file << "from matplotlib.patches import Circle" << endl
		 << "import matplotlib.pyplot as plt" << endl << endl;

	int x0 = 0;
	trav_method(IN2);
	for(iterator it = begin(); it != end(); it++, x0++)
	{
		it.ptr()->x0 = x0;
		it.ptr()->y0 = -(depth(it.ptr()));
	}

	for(iterator it = begin(); it != end(); it++)
	{
		auto child = it.ptr()->lchild;
		if(child)
		{
			connect(file, it.ptr()->x0, it.ptr()->y0, child->x0, child->y0);
		}
		child = it.ptr()->rchild;
		if(child)
		{
			connect(file, it.ptr()->x0, it.ptr()->y0, child->x0, child->y0);
		}
	}

	for(iterator it = begin(); it != end(); it++)
	{
		string face_color, font_color;
		switch(it.ptr()->color)
		{
			case 0: face_color = "w"; font_color = "k"; break;
			case 1: face_color = "#282923"; font_color = "w"; break;
			case 2: face_color = "r"; font_color = "w"; break;
		}
		circle(file, it.ptr()->x0, it.ptr()->y0, **it, face_color, font_color);
	}

	file << "plt.axis('scaled')" << endl
		 <<	"plt.axis('equal')" << endl << endl
		 << "plt.axis('off')" << endl
		 << "plt.tight_layout()" << endl
		 << "fig = plt.gcf()" << endl
		 << "fig.canvas.set_window_title('" << title << "')" << endl
		 << "plt.show()" << endl;

	file.close();
	system(("python \"Figures/" + title + ".py\"").data());
}

#endif