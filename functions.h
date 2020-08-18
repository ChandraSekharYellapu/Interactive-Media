

#ifndef IM_project_3_functions_h
#define IM_project_3_functions_h


#endif

#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

/*              Below are the three functions you need to implement                                    */


/*Render all the triangles: tells OpenGL all the triangles coordinates. You need to consider two types of rendering: render the mesh version or the solid version. You may need the variable "mesh_only" defined in the "data.h" file. */
void renderAllTriangles()
{
    //Implement this function
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (int i = 0; i < triangles_list.size(); i++)
    {
        if (mesh_only)
        {
            glBegin(GL_LINE_LOOP);
        }
        else
        {
            glBegin(GL_TRIANGLES);
        }

        int point_0 = triangles_list[i].v_index[0];
        int point_1 = triangles_list[i].v_index[1];
        int point_2 = triangles_list[i].v_index[2];



        glColor3f(triangles_list[i].c[0].c[0], triangles_list[i].c[0].c[1], triangles_list[i].c[0].c[2]);
        glVertex3f(vertice_list[point_0].x, vertice_list[point_0].y, vertice_list[point_0].z);

        glColor3f(triangles_list[i].c[1].c[0], triangles_list[i].c[1].c[1], triangles_list[i].c[1].c[2]);
        glVertex3f(vertice_list[point_1].x, vertice_list[point_1].y, vertice_list[point_1].z);

        glColor3f(triangles_list[i].c[2].c[0], triangles_list[i].c[2].c[1], triangles_list[i].c[2].c[2]);
        glVertex3f(vertice_list[point_2].x, vertice_list[point_2].y, vertice_list[point_2].z);
        glEnd();
    }
glutSwapBuffers();
}


/*Rotate the Teddy through mouse driving. You need to apply the transformation matrix on all the vertices*/
void rotateTeddy()
{
    //Implement this function

	Mat R_x, R_y, R_z;
	Mat T;
	
	R_x.normalize();
	R_y.normalize();
	R_z.normalize();
	T.normalize();
	
	/*rotation matrix on x axis */
	R_x.matrix[1][1] = cos(theta_x);
	R_x.matrix[1][2] = -sin(theta_x);
	R_x.matrix[2][1] = sin(theta_x);
	R_x.matrix[2][2] = cos(theta_x);

	/*rotation matrix on y axis */
	R_y.matrix[0][0] = cos(theta_y);
	R_y.matrix[0][2] = sin(theta_y);
	R_y.matrix[2][0] = -sin(theta_y);
	R_y.matrix[2][2] = cos(theta_y);

	/*rotation matrix on z axis */
	R_z.matrix[0][0] = cos(theta_z);
	R_z.matrix[0][1] = -sin(theta_z);
	R_z.matrix[1][0] = sin(theta_z);
	R_z.matrix[1][1] = cos(theta_z);

	/* transaltion matrix*/
	T.matrix[0][3] = shear_x;
	T.matrix[1][3] = shear_y;


	Mat P=T * R_x * R_y * R_z;
	Mat P = T * R_x * R_y;

	for (int i = 0; i < vertice_list.size(); i++)
	{
		Vertex old_v, new_v;
		old_v.matrix[0] = vertice_list[i].x;
		old_v.matrix[1] = vertice_list[i].y;
		old_v.matrix[2] = vertice_list[i].z;
		old_v.matrix[3] = 1.0;

		old_v.matrix[4]= {vertice_list[i].x, vertice_list[i].y, vertice_list[i].z, 1.0 };
		new_v = P * old_v;

		vertice_list[i].x = new_v.matrix[0] / new_v.matrix[3];
		vertice_list[i].y = new_v.matrix[1] / new_v.matrix[3];
		vertice_list[i].z = new_v.matrix[2] / new_v.matrix[3];

	}

	theta_x = 0;
	theta_y = 0;
	theta_z = 0;
	shear_x = 0;
	shear_y = 0;
	shear_z = 0;
}
    

    
}

/*Similar to the rotation function above but re-shape the bear by apply different rotation matrices to different parts of the object*/
void reshapeTeddy()
{
    //Implement this function
     glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (65.0, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}


/*      Only the above three functions need your implementation. You don't need to do any change on the code below */



inline double to_int(std::string const& str) {
    std::istringstream ss(str);
    
    int d;
    ss >> d;
    
    /* eat up trailing whitespace if there was a double read, and ensure
     * there is no character left. the eof bit is set in the case that
     * `std::ws` tried to read beyond the stream. */
    if(!(ss && (ss >> std::ws).eof()))
        exit(1);
    
    return d;
}

inline float to_float(std::string const& str) {
    std::istringstream ss(str);
    
    float f;
    ss >> f;
    
    /* eat up trailing whitespace if there was a double read, and ensure
     * there is no character left. the eof bit is set in the case that
     * `std::ws` tried to read beyond the stream. */
    if(!(ss && (ss >> std::ws).eof()))
        exit(1);
    
    return f;
}


inline char* to_char(string s)
{
    char *a=new char[s.size()+1];
    a[s.size()]=0;
    memcpy(a,s.c_str(),s.size());
    return a;
}




/*Do the shading on each triangle*/
void trianglesShading()
{

    {
        /*Make all the triangles the same color*/
        for(int i = 0; i < triangles_list.size(); i++) //triangle index
        {
            for(int j = 0; j < 3; j++) //vertex index
            {
                for(int k = 0; k < 3; k++) //color channel index
                {
                    triangles_list[i].c[j].channel[k] = bunny_color.channel[k];
                    
                }
            }
        }
    }
    
}

void initialize()
{
    
    light.x = 0;
    light.y = 0;
    light.z = 50;
    light.c.channel[0] = 0.8;
    light.c.channel[1] = 0.8;
    light.c.channel[2] = 0.8;
    
    light.normalize();
    
    light.c.channel[0] = 0.9;
    light.c.channel[1] = 0.9;
    light.c.channel[2] = 0.9;
    
    ambient_color.channel[0] = 0.3;
    ambient_color.channel[1] = 0.3;
    ambient_color.channel[2] = 0.3;
    
    bunny_color.channel[0] = 0.8;
    bunny_color.channel[1] = 0.8;
    bunny_color.channel[2] = 0.8;
    
    phong_color.channel[0] = 0.8;
    phong_color.channel[1] = 0.8;
    phong_color.channel[2] = 0.8;
    
    view_pos.x = 0.0f;
    view_pos.y = 0.0f;
    view_pos.z = 50.0f;
}

void loadObjFiles(char *filename, vector<Vertex> &vertice_list, vector<Triangle> &triangles_list )
{
    ifstream myfile (filename);
    string line;
    string valueX, valueY, valueZ, v;
    string idx0, idx1, idx2, f;
    
    int n = 0;
    while(!myfile.eof())
    {
        getline (myfile, line);
        if (line[0] == 'v')
        {
            std::istringstream iss( line );
            iss >> v >> valueX>> valueY>> valueZ;
            Vertex v;
            v.x = (GLfloat)to_float(valueX);
            v.y = (GLfloat)to_float(valueY);
            v.z = (GLfloat)to_float(valueZ);
            // v.normalize();
            
            
            /* By default, the initial colors for all the vertices are grey */
            for(int c = 0; c < 3; c++)
            {
                v.c.channel[c] = bunny_color.channel[c];
            }
            vertice_list.push_back(v);
        }
        if( line[0] == 'f')
        {
            std::istringstream iss( line );
            iss >> f >> idx0 >> idx1 >> idx2;
            int i0 = to_int(idx0) - 1;
            int i1 = to_int(idx1) - 1;
            int i2 = to_int(idx2) - 1;
            
            Triangle triangle;
            triangle.v_idx[0] = i0;
            triangle.v_idx[1] = i1;
            triangle.v_idx[2] = i2;
            
            triangle.c[0] = vertice_list[i0].c;
            triangle.c[1] = vertice_list[i1].c;
            triangle.c[2] = vertice_list[i2].c;
            triangles_list.push_back(triangle);
        }
    }
    
    
    /* Check what is the centroid value */
    float x = .0f;
    float y = .0f;
    float z = .0f;
    for(int i = 0; i < vertice_list.size(); i++)
    {
        x += vertice_list[i].x;
        y += vertice_list[i].y;
        z += vertice_list[i].z;
    }
    x /= (float)vertice_list.size();
    y /= (float)vertice_list.size();
    z /= (float)vertice_list.size();
    
    center.x = x;
    center.y = y;
    center.z = z;
    printf("center: (%f, %f, %f)\n", x, y, z);
}
