#version 330 core

//in vec4 vertexColor;
//in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 
uniform Material material;

//uniform sampler2D ourTexture;
//uniform sampler2D ourFace;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;

out vec4 FragColor;

void main() {
   //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
   //FragColor = mix(texture(ourTexture, TexCoord), texture(ourFace, TexCoord), 0.2);
   //FragColor = vec4(objColor * ambientColor, 1.0) * mix(texture(ourTexture, TexCoord), texture(ourFace, TexCoord), 0.2);
   vec3 lightDir = normalize(lightPos - FragPos);
   vec3 reflectVec = reflect(-lightDir, Normal);
   vec3 cameraVec = normalize(cameraPos - FragPos);
   
   // specular 
   float specularAmout = pow( max( dot(reflectVec, cameraVec), 0), material.shininess);
   vec3 specular = texture( material.specular, TexCoord).rgb * specularAmout * lightColor;
   
   // diffuse
   vec3 diffuse = texture(material.diffuse, TexCoord).rgb * max( dot(lightDir, Normal), 0) * lightColor;
   //vec3 diffuse = texture(material.diffuse, TexCoord).rgb;

   // ambient
   vec3 ambient = texture(material.diffuse, TexCoord).rgb * ambientColor;

   FragColor = vec4( (ambient + diffuse + specular)*objColor, 1.0 );

}