io.write( "[lua] These args were passed into the script from C\n" );

BLEND = { SRC_ALPHA=1, ONE_MINUS_SRC_ALPHA=2, ZERO = 3}
Color = 0
--2D = 0

shader = { 
   "name = Tutorial/Textured Colored",
   Properties = {
      _Color = { "Main Color", "Color", {1,1,1,0.5} },
      _MainTex = { "Texture", "2D", "white" },
   },

   SubShader = {
      P0 = {
            --blend = { BLEND.SRC_ALPHA, BLEND.ONE_MINUS_SRC_ALPHA, BLEND.ZERO },
            GL_DISABLE_ = { GL_BLEND },
            GL_BLEND_FUNC = { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA },
            GL_FRAGMENT_SHADER = "",
            GL_VERTEX_SHADER = "",
      },
      P1 = {
            --blend = { BLEND.SRC_ALPHA, BLEND.ONE_MINUS_SRC_ALPHA, BLEND.ZERO },
            GL_DISABLE__ = { GL_BLEND },
            GL_BLEND_FUNC = { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA },
            GL_FRAGMENT_SHADER = "",
            GL_VERTEX_SHADER = "",
      }
   }
}

--[[
shader = { "Tutorial/Textured Colored"

   properties = {
       _Color ("Main Color", Color) = (1,1,1,0.5)
       _MainTex ("Texture", 2D) = "white" { }
   }
   SubShader = {
      pass = {
      }
   }
}

]]
--[[
Shader "Tutorial/Textured Colored" {
   Properties {
       _Color ("Main Color", Color) = (1,1,1,0.5)
       _MainTex ("Texture", 2D) = "white" { }
   }
   SubShader {
       Pass {

       CGPROGRAM
       #pragma vertex vert
       #pragma fragment frag

       #include "UnityCG.cginc"

       fixed4 _Color;
       sampler2D _MainTex;

       struct v2f {
           float4 pos : SV_POSITION;
           float2 uv : TEXCOORD0;
       };

       float4 _MainTex_ST;

       v2f vert (appdata_base v)
       {
           v2f o;
           o.pos = mul (UNITY_MATRIX_MVP, v.vertex);
           o.uv = TRANSFORM_TEX (v.texcoord, _MainTex);
           return o;
       }

       fixed4 frag (v2f i) : SV_Target
       {
           fixed4 texcol = tex2D (_MainTex, i.uv);
           return texcol * _Color;
       }
       ENDCG

       }
   }
}]]

--return temp,9,1