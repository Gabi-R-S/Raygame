// Raygame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <raylib.h>
#include<raymath.h>
#include <vector>
#include <rlgl.h>

struct Floor 
{
    std::vector<bool> map;
    unsigned int width;
    unsigned int height;
};

struct InitializeLevelInfo
{
    Floor floorInfo;
    Texture imageTex;
    Model mapModel;
};

InitializeLevelInfo GenerateLevel(const Image& image) 
{
    auto width = image.width;
    auto height = image.height;
    auto map = std::vector<bool>(width * height);
    map.resize(width * height);
    char* data = (char*)image.data;
    for (auto y = 0;y<height; y++) {
        for (auto x = 0;x<width; x++) {

            auto color = GetImageColor(image, x, y);
            map[x + y * width] = color.r == 255&&color.a!=0;
        }
    }
    Floor _floor = { map,width,height };
    Texture mapTex = LoadTextureFromImage(image);


    std::vector<Color> colors;
    std::vector<Vector3> verts;
    std::vector<Vector3> normals;
    for (auto y = 0; y < height; y++) {
        for (auto x = 0; x < width; x++) {
            //set verts
            auto index = x + y * width;
            if (map[index]) 
            {
                //top and bottom faces
                verts.push_back({(float)x- 0.5f,(float)-0.5f,(float)y- 0.5f });

                verts.push_back({ (float)x+0.5f,(float)-0.5f,(float)y- 0.5f });

                verts.push_back({ (float)x- 0.5f,(float)-0.5f,(float)y+ 0.5f });

               
                verts.push_back({ (float)x + 0.5f,(float)-0.5f,(float)y - 0.5f });

                verts.push_back({ (float)x - 0.5f,(float)-0.5f,(float)y + 0.5f });

                verts.push_back({ (float)x + 0.5f,(float)-0.5f,(float)y + 0.5f });

                for (auto i = 0; i < 6; i++) 
                {
                    normals.push_back({0.0f,1.0f ,0.0f });
                }

                verts.push_back({ (float)x - 0.5f,(float)0.5f,(float)y - 0.5f });

                verts.push_back({ (float)x + 0.5f,(float)0.5f,(float)y - 0.5f });

                verts.push_back({ (float)x - 0.5f,(float)0.5f,(float)y + 0.5f });


                verts.push_back({ (float)x + 0.5f,(float)0.5f,(float)y - 0.5f });

                verts.push_back({ (float)x - 0.5f,(float)0.5f,(float)y + 0.5f });

                verts.push_back({ (float)x + 0.5f,(float)0.5f,(float)y + 0.5f });
                
                for (auto i = 0; i < 6; i++)
                {
                    normals.push_back({ 0.0f,-1.0f ,0.0f });
                }

                for (auto i = 0; i < 12; i++) {
                    colors.push_back(WHITE);
                }
                //end of top and bottom faces


                Color slightlyDarker = {230,230,250,255};
                //add walls
                if (x + 1 != width) 
                {
                    if (!map[index+1])
                    {

                        verts.push_back({ (float)x + 0.5f,(float)-0.5f,(float)y - 0.5f });

                        verts.push_back({ (float)x + 0.5f,(float)-0.5f,(float)y + 0.5f });

                        verts.push_back({ (float)x + 0.5f,(float)+0.5f,(float)y + 0.5f });


                        verts.push_back({ (float)x + 0.5f,(float)+0.5f,(float)y + 0.5f });
                        verts.push_back({ (float)x + 0.5f,(float)+0.5f,(float)y - 0.5f });
                        verts.push_back({ (float)x + 0.5f,(float)-0.5f,(float)y - 0.5f });
                        
                        for (auto i = 0; i < 6; i++)
                        {
                            normals.push_back({ -1.0f,0.0f ,0.0f });
                        } 
                        for (auto i = 0; i < 6; i++) {
                            colors.push_back(slightlyDarker);
                        }
                    }
                }

                if (x  != 0)
                {
                    if (!map[index -1])
                    {
                        verts.push_back({ (float)x - 0.5f,(float)-0.5f,(float)y - 0.5f });

                        verts.push_back({ (float)x - 0.5f,(float)-0.5f,(float)y + 0.5f });

                        verts.push_back({ (float)x - 0.5f,(float)+0.5f,(float)y + 0.5f });


                        verts.push_back({ (float)x - 0.5f,(float)+0.5f,(float)y + 0.5f });
                        verts.push_back({ (float)x - 0.5f,(float)+0.5f,(float)y - 0.5f });
                        verts.push_back({ (float)x - 0.5f,(float)-0.5f,(float)y - 0.5f });

                        for (auto i = 0; i < 6; i++)
                        {
                            normals.push_back({ 1.0f,0.0f ,0.0f });
                        }
                        for (auto i = 0; i < 6; i++) {
                            colors.push_back(slightlyDarker);
                        }
                    }
                }


                if (y!=0)
                {
                    if (!map[index - width])
                    {
                        verts.push_back({ (float)x - 0.5f,(float)-0.5f,(float)y - 0.5f });

                        verts.push_back({ (float)x + 0.5f,(float)-0.5f,(float)y - 0.5f });

                        verts.push_back({ (float)x + 0.5f,(float)+0.5f,(float)y - 0.5f });


                        verts.push_back({ (float)x + 0.5f,(float)+0.5f,(float)y - 0.5f });
                        verts.push_back({ (float)x - 0.5f,(float)+0.5f,(float)y - 0.5f });
                        verts.push_back({ (float)x - 0.5f,(float)-0.5f,(float)y - 0.5f });

                        for (auto i = 0; i < 6; i++)
                        {
                            normals.push_back({ 0.0f,0.0f ,1.0f });
                        }
                        for (auto i = 0; i < 6; i++) {
                            colors.push_back(slightlyDarker);
                        }
                    }
                }
                if (y != height)
                {
                    if (!map[index + width])
                    {
                        verts.push_back({ (float)x - 0.5f,(float)-0.5f,(float)y + 0.5f });

                        verts.push_back({ (float)x + 0.5f,(float)-0.5f,(float)y + 0.5f });

                        verts.push_back({ (float)x + 0.5f,(float)+0.5f,(float)y + 0.5f });


                        verts.push_back({ (float)x + 0.5f,(float)+0.5f,(float)y + 0.5f });
                        verts.push_back({ (float)x - 0.5f,(float)+0.5f,(float)y + 0.5f });
                        verts.push_back({ (float)x - 0.5f,(float)-0.5f,(float)y + 0.5f });

                        for (auto i = 0; i < 6; i++)
                        {
                            normals.push_back({ 0.0f,0.0f ,-1.0f });
                        }
                        for (auto i = 0; i < 6; i++) {
                            colors.push_back(slightlyDarker);
                        }
                    }
                }


            }
        }
    }


    Mesh mapMesh = {0};
    mapMesh.vertexCount = verts.size();
    mapMesh.triangleCount = mapMesh.vertexCount / 3;
    //oh no, horrible c code in action
    mapMesh.vertices = (float*)MemAlloc(mapMesh.vertexCount * 3 * sizeof(float));    // 3 vertices, 3 coordinates each (x, y, z)
    //mapMesh.texcoords = (float*)MemAlloc(mapMesh.vertexCount * 2 * sizeof(float));   // 3 vertices, 2 coordinates each (x, y)
    mapMesh.normals = (float*)MemAlloc(mapMesh.vertexCount * 3 * sizeof(float));
    mapMesh.colors= (unsigned char*)MemAlloc(mapMesh.vertexCount * 4 * sizeof(unsigned char));
    for (size_t i = 0; i < verts.size(); i++)
    {
        mapMesh.vertices[i*3] = verts[i].x;
        mapMesh.vertices[i * 3+1] = verts[i].y;
        mapMesh.vertices[i * 3+2] = verts[i].z;
       
        mapMesh.colors[i * 4] = colors[i].r;
        mapMesh.colors[i * 4+1] = colors[i].g;
        mapMesh.colors[i * 4+2] = colors[i].b;
        mapMesh.colors[i * 4+3] = colors[i].a;

        mapMesh.normals[i * 3] = normals[i].x;
        mapMesh.normals[i * 3+1] = normals[i].y;
        mapMesh.normals[i * 3+2] = normals[i].z;

    }
    UploadMesh(&mapMesh,false);


    return { _floor,mapTex,LoadModelFromMesh(mapMesh)};
}

Vector3 GetCamLookDir( float rotation)
{
    return  { sin(rotation), 0.0f, cos(rotation) };
}
Vector3 GetCamTarget(Vector3 position, float rotation)
{
    return Vector3Add(position, GetCamLookDir(rotation));
}
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 850;
    const int screenHeight = 550;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "DarkMap");
    rlDisableBackfaceCulling();
    SetTargetFPS(120);  


    //--------------------------------------------------------------------------------------
    Image levelImage=LoadImage("C:/CodingProjects/C++/RaygameImprovement/TestLevel.png");
    auto level = GenerateLevel(levelImage);
    levelImage = LoadImage("C:/CodingProjects/C++/RaygameImprovement/TestLevel2.png");
    auto secondLevel = GenerateLevel(levelImage);
    
    Camera camera = { 0 };
    
    camera.position = { 5.0f, 0.0f, 5.0f };
    camera.target = Vector3Add(camera.position, { 0.0f, 0.0f, 0.5f }) ;
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 30.0f;
    camera.projection = CAMERA_PERSPECTIVE;
   
    float camRotation=0.0f;
    Vector3 camLookDir=GetCamLookDir(camRotation);
    
    Shader shader = LoadShader("C:/CodingProjects/C++/RaygameImprovement/DistanceShader.vert","C:/CodingProjects/C++/RaygameImprovement/DistanceShader.frag");

    int locationFar = GetShaderLocation(shader, "farColor");

    float far [4] = {0.05f,0.02f,0.07f,1.0f};
    SetShaderValue(shader, locationFar, &far, SHADER_UNIFORM_VEC4);
    
    level.mapModel.materials[0].shader=shader;
    secondLevel.mapModel.materials[0].shader = shader;
   
    
    Vector3 firstFloorLadder = {3.f,0.0f,54.f };
    Vector3 secondFloorLadder = { 60.f ,0.f,57.f };

    Model ladder = LoadModelFromMesh(GenMeshCone(0.4f,0.6f,12));
    ladder.materials[0].shader = shader;

    // Main game loop
    bool firstLevel = true;
    bool cameOutOfLadder=true;

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        camRotation += (-IsKeyDown((KEY_RIGHT))+IsKeyDown(KEY_LEFT))*0.02f;
        camLookDir = GetCamLookDir(camRotation);
        Vector3 nextPosition= Vector3Add(Vector3Scale(camLookDir, (IsKeyDown((KEY_UP)) - IsKeyDown(KEY_DOWN)) * (0.025f+IsKeyDown(KEY_LEFT_SHIFT)*0.03f)), camera.position);
        Vector3 nextPositionExtra=Vector3Add(Vector3Scale(camLookDir, 1.7f*((IsKeyDown((KEY_UP)) - IsKeyDown(KEY_DOWN)) * (0.025f + IsKeyDown(KEY_LEFT_SHIFT) * 0.03f))), camera.position);

        unsigned int index = round(nextPositionExtra.z)*level.floorInfo.width+round(nextPositionExtra.x);
        if (firstLevel)
        {


            if (index < level.floorInfo.map.size())
            {
                if (level.floorInfo.map[index])
                {
                    camera.position = nextPosition;
                }

            }
            if (cameOutOfLadder == true) {
                if (Vector3LengthSqr(Vector3Subtract(nextPosition, firstFloorLadder)) <= 0.1f) 
                { firstLevel = false; 
                camera.position = secondFloorLadder;
                cameOutOfLadder = false; }
            }
            else {
                
                if (Vector3LengthSqr(Vector3Subtract(nextPosition, firstFloorLadder)) > 0.1f) { cameOutOfLadder = true; }
            }
        }
        else 
        {
            if (index < secondLevel.floorInfo.map.size())
            {
                if (secondLevel.floorInfo.map[index])
                {
                    camera.position = nextPosition;
                }

            }
            if (cameOutOfLadder == true) {
                if (Vector3LengthSqr(Vector3Subtract(nextPosition, secondFloorLadder)) <= 0.1f) 
                { firstLevel = true;
                camera.position = firstFloorLadder; 
                cameOutOfLadder = false; }
            }
            else {
                if (Vector3LengthSqr(Vector3Subtract(nextPosition, secondFloorLadder)) > 0.1f) { cameOutOfLadder = true; }
            }
        }
        camera.target = Vector3Add(camera.position,Vector3Scale(camLookDir,0.5f));
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
     
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground({ (unsigned char)(far[0]*255.0f),(unsigned char)(far[1] * 255.0f) ,(unsigned char)(far[2] * 255.0f) ,255});

        BeginMode3D(camera);
        if (firstLevel)
        {
            DrawModel(level.mapModel, { 0,0,0 }, 1, WHITE);
            DrawModel(ladder, Vector3Add(firstFloorLadder, {0,-0.2f,0}), 1, RED);

        }
        else 
        {
            DrawModel(secondLevel.mapModel, { 0,0,0 }, 1, WHITE);
            DrawModel(ladder, Vector3Add(secondFloorLadder, { 0,0.2f,0 }), -1, RED);
        }
        EndMode3D();
        if (firstLevel)
        {
            DrawTextureEx(level.imageTex, { 0,0 }, 0, 4, WHITE);

            DrawRectangle(firstFloorLadder.x * 4, firstFloorLadder.z * 4, 4, 4, BLUE);
        }
        else 
        {
            DrawTextureEx(secondLevel.imageTex, { 0,0 }, 0, 4, WHITE);
            DrawRectangle(secondFloorLadder.x * 4, secondFloorLadder.z * 4, 4, 4, BLUE);
        }
        DrawRectangle(camera.position.x * 4, camera.position.z * 4, 4, 4, DARKPURPLE);
 
        //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

