void initSkybox(vector<const GLchar*> faces) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glActiveTexture(GL_TEXTURE0);

    int width, height;
    unsigned char* image;

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for(GLuint i = 0; i < faces.size(); i++) {
        image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
            GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
        );
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return textureID;
}

void initNightBox(){
  vector<const GLchar*> faces;
  faces.push_back("assets/moonlightrt.bmp");
  faces.push_back("assets/moonlightlt.bmp");
  faces.push_back("assets/moonlighttup.bmp");
  faces.push_back("assets/moonlightdn.bmp");
  faces.push_back("assets/moonlightbk.bmp");
  faces.push_back("assets/moonlightft.bmp");
  GLuint cubemapTexture = initSkybox(faces);
}
