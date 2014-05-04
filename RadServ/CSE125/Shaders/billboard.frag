#version 400                                                                       
                                                                                    
uniform sampler2D texUnit;                                                        
                                                                                    
in vec2 TexCoord;                                                                   
out vec4 FragColor;                                                                 
                                                                                    
void main()                                                                         
{                                                                                   
    FragColor = texture2D(texUnit, TexCoord);                                     
    
    /*                                                                                
    if (FragColor.r <= 0.1 && FragColor.g <= 0.1 && FragColor.b <= 0.1) {
        discard;                                                                    
    }   
    */        

    if(FragColor.a<0.1){
    	discard;
    }                                                                    
}