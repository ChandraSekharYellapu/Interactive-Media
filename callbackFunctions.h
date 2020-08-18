

#ifndef IM_project_3_callbackFunctions_h
#define IM_project_3_callbackFunctions_h


#endif

// Do not need to do any change about these variables
GLfloat light_x = .0f;
GLfloat light_y = .0f;
GLfloat light_z = 10.0f;
GLfloat light_position[] = { 0.0, 0.0, 5, 1.0 };  /* Infinite light location. */
GLfloat low_sh[] = {5.0};

/*material data*/
GLfloat material_color1[] = { 0.1, 0.7, .0, 1.0 }; //ambient 1
GLfloat material_color2[] = { 1.0, 0.0, .0, 1.0 }; //ambient 2
GLfloat material_color3[] = { .5, 0.5, 0.5, 1.0 }; //specular


GLfloat light_direction[] = { .0, .0, -1.0 };
// Do not need to do any change about the variables above

GLfloat angle = 100;

//You many need the variable mesh_only to switch the views
void onKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            exit(1);
            
            break;
        case 'm':
            mesh_only = (mesh_only == 1)?0:1;
            glutPostRedisplay();
            break;
        case '1':
            shading_type = 1;
            glutPostRedisplay();
            break;
        case '0':
            shading_type = 0;
            glutPostRedisplay();
            break;
        case '2':
            shading_type = 2;
            glutPostRedisplay();
            break;
        
        default:
            break;
    }
}

void onMouse(int button, int state, int x, int y)
{
    
    GLint specialKey = glutGetModifiers();
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                mouse_down = 1;
                current_x = x;
                current_y = y;
                if (specialKey == GLUT_ACTIVE_SHIFT)
                {
                    change_mode = 1;
                }
                else
                {
                    change_mode = 0;
                }
            }
            else if (state == GLUT_UP)
            {
                mouse_down = 0;
            }
            break;
            
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                
                break;
            
        default:
            break;
            
    }
    
}

//you may need the theta_x and theta_y as angles for rotation matrix generation
void onMouseMotion(int x, int y)
{
    if (mouse_down == 1)
    {
        if (change_mode == 0)
        {
            theta_y += static_cast<float>(x - current_x) / 100.f;
            theta_x += static_cast<float>(y - current_y) / 100.f;
        }
        else{
            theta_y += static_cast<float>(x - current_x) / 100.f;
            theta_x += static_cast<float>(-y + current_y) / 100.f;
        }
        
        current_x = x;
        current_y = y;
    }
    glutPostRedisplay();
}



/*Define the 3D objects that want to show*/
void onDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
 
    
    
    
    /* Transform the points */
    if(mouse_down == 1) //only when the mouse is dragging, this function is called
    {
        if (change_mode == 0)
            rotateTeddy();
        else
            reshapeTeddy();
    }
    
    /* Do the shading on Traingles which is about the color part, you don't need touch this function */
    trianglesShading();
    
    /* Render all the triangles */
    renderAllTriangles();
    
    
    //Below is an example of showing how to draw a line and a triangle
    glColor3d(1.0, 0, 0);
     glBegin(GL_LINES);
       glVertex3d(-20, 0.56, 0.9);
       glVertex3d(20, 0.56, 0.9);
    glEnd();
 
    glBegin(GL_TRIANGLES);
        glColor3f(0, 0.8, 0);
        glVertex3d(0.3, 7.5, 1.0);
        glVertex3d(0.3, -7.5, 1.0);
        glVertex3d(3.3, 0.5, 0.0);
    glEnd();
    
    glFlush(); //clear the memory
    
    
    //You don't need to do anything about the code below
      light_position[0] = light_x;
            light_position[1] = light_y;
            light_position[2] = light_z;
            glLightfv(GL_LIGHT0, GL_POSITION, light_position);
            glMaterialfv(GL_FRONT, GL_AMBIENT, material_color3);
            glEnable(GL_LIGHT0);
            glEnable(GL_LIGHTING);
    
          
    
                glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.2);
                glMaterialfv(GL_FRONT, GL_AMBIENT, material_color1);
                glMaterialfv(GL_FRONT, GL_SPECULAR, material_color3);
                glMaterialfv(GL_FRONT, GL_SHININESS, low_sh);
           
}
