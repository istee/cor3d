#include "Materials.h"

using namespace cagd;

Material::Material(
    const Color4& front_ambient,
    const Color4& front_diffuse,
    const Color4& front_specular,
    const Color4& front_emissive,
    GLfloat front_shininess,

    const Color4& back_ambient,
    const Color4& back_diffuse,
    const Color4& back_specular,
    const Color4& back_emissive,
    GLfloat back_shininess):

    _front_ambient	(front_ambient),
    _front_diffuse	(front_diffuse),
    _front_specular	(front_specular),
    _front_emissive	(front_emissive),
    _front_shininess	(front_shininess),

    _back_ambient	(back_ambient),
    _back_diffuse	(back_diffuse),
    _back_specular	(back_specular),
    _back_emissive	(back_emissive),
    _back_shininess	(back_shininess)
{
}

GLvoid Material::SetAmbientColor(GLenum face, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    switch (face)
    {
    case GL_FRONT:
        _front_ambient.r() = r;
        _front_ambient.g() = g;
        _front_ambient.b() = b;
        _front_ambient.a() = a;
    break;

    case GL_BACK:
        _back_ambient.r() = r;
        _back_ambient.g() = g;
        _back_ambient.b() = b;
        _back_ambient.a() = a;
    break;

    case GL_FRONT_AND_BACK:
        _front_ambient.r() = r;
        _front_ambient.g() = g;
        _front_ambient.b() = b;
        _front_ambient.a() = a;

        _back_ambient.r()  = r;
        _back_ambient.g()  = g;
        _back_ambient.b()  = b;
        _back_ambient.a()  = a;
    break;
    }
}

GLvoid Material::SetAmbientColor(GLenum face, const Color4& c)
{
    SetAmbientColor(face, c.r(), c.g(), c.b(), c.a());
}

GLvoid Material::SetDiffuseColor(GLenum face, const Color4& c)
{
    switch (face)
    {
    case GL_FRONT:
        _front_diffuse.r() = c.r();
        _front_diffuse.g() = c.g();
        _front_diffuse.b() = c.b();
        _front_diffuse.a() = c.a();
    break;

    case GL_BACK:
        _back_diffuse.r() = c.r();
        _back_diffuse.g() = c.g();
        _back_diffuse.b() = c.b();
        _back_diffuse.a() = c.a();
    break;

    case GL_FRONT_AND_BACK:
        _front_diffuse.r() = c.r();
        _front_diffuse.g() = c.g();
        _front_diffuse.b() = c.b();
        _front_diffuse.a() = c.a();

        _back_diffuse.r() = c.r();
        _back_diffuse.g() = c.g();
        _back_diffuse.b() = c.b();
        _back_diffuse.a() = c.a();
    break;
    }
}

GLvoid Material::SetDiffuseColor(GLenum face, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    switch (face)
    {
    case GL_FRONT:
        _front_diffuse.r() = r;
        _front_diffuse.g() = g;
        _front_diffuse.b() = b;
        _front_diffuse.a() = a;
    break;

    case GL_BACK:
        _back_diffuse.r() = r;
        _back_diffuse.g() = g;
        _back_diffuse.b() = b;
        _back_diffuse.a() = a;
    break;

    case GL_FRONT_AND_BACK:
        _front_diffuse.r() = r;
        _front_diffuse.g() = g;
        _front_diffuse.b() = b;
        _front_diffuse.a() = a;

        _back_diffuse.r()  = r;
        _back_diffuse.g()  = g;
        _back_diffuse.b()  = b;
        _back_diffuse.a()  = a;
    break;
    }
}

GLvoid Material::SetSpecularColor(GLenum face, const Color4& c)
{
    switch (face)
    {
    case GL_FRONT:
        _front_specular.r() = c.r();
        _front_specular.g() = c.g();
        _front_specular.b() = c.b();
        _front_specular.a() = c.a();
    break;

    case GL_BACK:
        _back_specular.r() = c.r();
        _back_specular.g() = c.g();
        _back_specular.b() = c.b();
        _back_specular.a() = c.a();
    break;

    case GL_FRONT_AND_BACK:
        _front_specular.r() = c.r();
        _front_specular.g() = c.g();
        _front_specular.b() = c.b();
        _front_specular.a() = c.a();

        _back_specular.r() = c.r();
        _back_specular.g() = c.g();
        _back_specular.b() = c.b();
        _back_specular.a() = c.a();
    break;
    }
}

GLvoid Material::SetSpecularColor(GLenum face, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    switch (face)
    {
    case GL_FRONT:
        _front_specular.r() = r;
        _front_specular.g() = g;
        _front_specular.b() = b;
        _front_specular.a() = a;
    break;

    case GL_BACK:
        _back_specular.r() = r;
        _back_specular.g() = g;
        _back_specular.b() = b;
        _back_specular.a() = a;
    break;

    case GL_FRONT_AND_BACK:
        _front_specular.r() = r;
        _front_specular.g() = g;
        _front_specular.b() = b;
        _front_specular.a() = a;

        _back_specular.r()  = r;
        _back_specular.g()  = g;
        _back_specular.b()  = b;
        _back_specular.a()  = a;
    break;
    }
}

GLvoid Material::SetEmissiveColor(GLenum face, const Color4& c)
{
    switch (face)
    {
    case GL_FRONT:
        _front_emissive.r() = c.r();
        _front_emissive.g() = c.g();
        _front_emissive.b() = c.b();
        _front_emissive.a() = c.a();
    break;

    case GL_BACK:
        _back_emissive.r() = c.r();
        _back_emissive.g() = c.g();
        _back_emissive.b() = c.b();
        _back_emissive.a() = c.a();
    break;

    case GL_FRONT_AND_BACK:
        _front_emissive.r() = c.r();
        _front_emissive.g() = c.g();
        _front_emissive.b() = c.b();
        _front_emissive.a() = c.a();

        _back_emissive.r() = c.r();
        _back_emissive.g() = c.g();
        _back_emissive.b() = c.b();
        _back_emissive.a() = c.a();
    break;
    }
}

GLvoid Material::SetEmissiveColor(GLenum face, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    switch (face)
    {
    case GL_FRONT:
        _front_emissive.r() = r;
        _front_emissive.g() = g;
        _front_emissive.b() = b;
        _front_emissive.a() = a;
    break;

    case GL_BACK:
        _back_emissive.r() = r;
        _back_emissive.g() = g;
        _back_emissive.b() = b;
        _back_emissive.a() = a;
    break;

    case GL_FRONT_AND_BACK:
        _front_emissive.r() = r;
        _front_emissive.g() = g;
        _front_emissive.b() = b;
        _front_emissive.a() = a;

        _back_emissive.r()  = r;
        _back_emissive.g()  = g;
        _back_emissive.b()  = b;
        _back_emissive.a()  = a;
    break;
    }
}

GLvoid Material::SetShininess(GLenum face, GLfloat shininess)
{
    switch (face)
    {
    case GL_FRONT:
        _front_shininess = shininess;
    break;

    case GL_BACK:
        _back_shininess = shininess;
    break;

    case GL_FRONT_AND_BACK:
        _front_shininess = shininess;
        _back_shininess = shininess;
    break;
    }
}

GLvoid Material::SetTransparency(GLfloat alpha)
{
    _front_ambient.a() = alpha;
    _front_diffuse.a() = alpha;
    _front_emissive.a() = alpha;
    _front_specular.a() = alpha;

    _back_ambient.a() = alpha;
    _back_diffuse.a() = alpha;
    _back_emissive.a() = alpha;
    _back_specular.a() = alpha;
}

GLboolean Material::IsTransparent() const
{
    if(_front_ambient.a() == 0.0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

GLvoid Material::Apply()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT,   &_front_ambient.r());
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   &_front_diffuse.r());
    glMaterialfv(GL_FRONT, GL_SPECULAR,  &_front_specular.r());
    glMaterialfv(GL_FRONT, GL_EMISSION,  &_front_emissive.r());
    glMaterialf (GL_FRONT, GL_SHININESS, _front_shininess);

    glMaterialfv(GL_BACK, GL_AMBIENT,    &_back_ambient.r());
    glMaterialfv(GL_BACK, GL_DIFFUSE,    &_back_diffuse.r());
    glMaterialfv(GL_BACK, GL_SPECULAR,   &_back_specular.r());
    glMaterialfv(GL_BACK, GL_EMISSION,   &_back_emissive.r());
    glMaterialf (GL_BACK, GL_SHININESS,  _back_shininess);
}

// brass
Material cagd::MatFBBrass = Material(
                        Color4(0.329412, 0.223529, 0.027451, 0.4),
                        Color4(0.780392, 0.568627, 0.113725, 0.6),
                        Color4(0.992157, 0.941176, 0.807843, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        27.8974,
                        Color4(0.329412, 0.223529, 0.027451, 0.4),
                        Color4(0.780392, 0.568627, 0.113725, 0.6),
                        Color4(0.992157, 0.941176, 0.807843, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        27.8974);

// emerald
Material cagd::MatFBEmerald = Material(
                        Color4(0.021500, 0.174500, 0.021500, 0.4),
                        Color4(0.075680, 0.614240, 0.075680, 0.6),
                        Color4(0.633000, 0.727811, 0.633000, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        76.8,
                        Color4(0.021500, 0.174500, 0.021500, 0.4),
                        Color4(0.075680, 0.614240, 0.075680, 0.6),
                        Color4(0.633000, 0.727811, 0.633000, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        76.8);

// gold
Material cagd::MatFBGold = Material(
                        Color4(0.247250, 0.199500, 0.074500, 0.4),
                        Color4(0.751640, 0.606480, 0.226480, 0.6),
                        Color4(0.628281, 0.555802, 0.366065, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        51.2,
                        Color4(0.247250, 0.199500, 0.074500, 0.4),
                        Color4(0.751640, 0.606480, 0.226480, 0.6),
                        Color4(0.628281, 0.555802, 0.366065, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        51.2);

// pearl
Material cagd::MatFBPearl = Material(
                        Color4(0.250000, 0.207250, 0.207250, 0.4),
                        Color4(1.000000, 0.829000, 0.829000, 0.6),
                        Color4(0.296648, 0.296648, 0.296648, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        11.264,
                        Color4(0.250000, 0.207250, 0.207250, 0.4),
                        Color4(1.000000, 0.829000, 0.829000, 0.6),
                        Color4(0.296648, 0.296648, 0.296648, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        11.264);

// ruby
Material cagd::MatFBRuby = Material(
                        Color4(0.174500, 0.011750, 0.011750, 0.4),
                        Color4(0.614240, 0.041360, 0.041360, 0.6),
                        Color4(0.727811, 0.626959, 0.626959, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        76.8,
                        Color4(0.174500, 0.011750, 0.011750, 0.4),
                        Color4(0.614240, 0.041360, 0.041360, 0.6),
                        Color4(0.727811, 0.626959, 0.626959, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        76.8);

// silver
Material cagd::MatFBSilver = Material(
                        Color4(0.192250, 0.192250, 0.192250, 0.4),
                        Color4(0.507540, 0.507540, 0.507540, 0.6),
                        Color4(0.508273, 0.508273, 0.508273, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        51.2,
                        Color4(0.192250, 0.192250, 0.192250, 0.4),
                        Color4(0.507540, 0.507540, 0.507540, 0.6),
                        Color4(0.508273, 0.508273, 0.508273, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        51.2);

// turquoise
Material cagd::MatFBTurquoise = Material(
                        Color4(0.100000, 0.187250, 0.174500, 0.4),
                        Color4(0.396000, 0.741510, 0.691020, 0.6),
                        Color4(0.297254, 0.308290, 0.306678, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        12.8,
                        Color4(0.100000, 0.187250, 0.174500, 0.4),
                        Color4(0.396000, 0.741510, 0.691020, 0.6),
                        Color4(0.297254, 0.308290, 0.306678, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        12.8);

// jade
Material cagd::MatFBJade = Material(
                        Color4(0.135, 0.2225, 0.1575, 0.4),
                        Color4(0.54, 0.89, 0.63, 0.6),
                        Color4(0.316228, 0.316228, 0.316228, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        12.8,
                        Color4(0.135, 0.2225, 0.1575, 0.4),
                        Color4(0.54, 0.89, 0.63, 0.6),
                        Color4(0.316228, 0.316228, 0.316228, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        12.8);

// obsidian
Material cagd::MatFBObsidian = Material(
                        Color4(0.05375, 0.05, 0.06625, 0.4),
                        Color4(0.18275, 0.17, 0.22525, 0.6),
                        Color4(0.332741, 0.328634, 0.346435, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        38.4,
                        Color4(0.05375, 0.05, 0.06625, 0.4),
                        Color4(0.18275, 0.17, 0.22525, 0.6),
                        Color4(0.332741, 0.328634, 0.346435, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        38.4);

// bronze
Material cagd::MatFBBronze = Material(
                        Color4(0.2125, 0.1275, 0.054, 0.4),
                        Color4(0.714, 0.4284, 0.18144, 0.6),
                        Color4(0.393548, 0.271906, 0.166721, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        25.6,
                        Color4(0.2125, 0.1275, 0.054, 0.4),
                        Color4(0.714, 0.4284, 0.18144, 0.6),
                        Color4(0.393548, 0.271906, 0.166721, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        25.6);

// chrome
Material cagd::MatFBChrome = Material(
                        Color4(0.25, 0.25, 0.25, 0.4),
                        Color4(0.4, 0.4, 0.4, 0.6),
                        Color4(0.774597, 0.774597, 0.774597, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        76.8,
                        Color4(0.25, 0.25, 0.25, 0.4),
                        Color4(0.4, 0.4, 0.4, 0.6),
                        Color4(0.774597, 0.774597, 0.774597, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        76.8);

// copper
Material cagd::MatFBCopper = Material(
                        Color4(0.19125, 0.0735, 0.0225, 0.4),
                        Color4(0.7038, 0.27048, 0.0828, 0.6),
                        Color4(0.256777, 0.137622, 0.086014, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        12.8,
                        Color4(0.19125, 0.0735, 0.0225, 0.4),
                        Color4(0.7038, 0.27048, 0.0828, 0.6),
                        Color4(0.256777, 0.137622, 0.086014, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        12.8);

// black plastic
Material cagd::MatPlasticBlack = Material(
                        Color4(0.0, 0.0, 0.0, 0.4),
                        Color4(0.01, 0.01, 0.01, 0.6),
                        Color4(0.50, 0.50, 0.50, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        32,
                        Color4(0.0, 0.0, 0.0, 0.4),
                        Color4(0.01, 0.01, 0.01, 0.6),
                        Color4(0.50, 0.50, 0.50, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        .32);

// cyan plastic
Material cagd::MatPlasticCyan = Material(
                        Color4(0.0, 0.1, 0.06, 0.4),
                        Color4(0.0, 0.50980392, 0.50980392, 0.6),
                        Color4(0.50196078, 0.50196078, 0.50196078, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        32,
                        Color4(0.0, 0.1, 0.06, 0.4),
                        Color4(0.0, 0.50980392, 0.50980392, 0.6),
                        Color4(0.50196078, 0.50196078, 0.50196078, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        32);

// green plastic
Material cagd::MatPlasticGreen = Material(
                        Color4(0.0, 0.0, 0.0, 0.4),
                        Color4(0.1, 0.35, 0.1, 0.6),
                        Color4(0.45, 0.55, 0.45, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        32,
                        Color4(0.0, 0.0, 0.0, 0.4),
                        Color4(0.1, 0.35, 0.1, 0.6),
                        Color4(0.45, 0.55, 0.45, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        32);

// red plastic
Material cagd::MatPlasticRed = Material(
                        Color4(0.0, 0.0, 0.0, 0.4),
                        Color4(0.5, 0.0, 0.0, 0.6),
                        Color4(0.7, 0.6, 0.6, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        32,
                        Color4(0.0, 0.0, 0.0, 0.4),
                        Color4(0.5, 0.0, 0.0, 0.6),
                        Color4(0.7, 0.6, 0.6, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        32);

// white plastic
Material cagd::MatPlasticWhite = Material(
                        Color4(0.0, 0.0, 0.0, 0.4),
                        Color4(0.55, 0.55, 0.55, 0.6),
                        Color4(0.70, 0.70, 0.70, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        32,
                        Color4(0.0, 0.0, 0.0, 0.4),
                        Color4(0.55, 0.55, 0.55, 0.6),
                        Color4(0.70, 0.70, 0.70, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        32);

// yellow plastic
Material cagd::MatPlasticYellow = Material(
                        Color4(0.0, 0.0, 0.0, 0.4),
                        Color4(0.5, 0.5, 0.0, 0.6),
                        Color4(0.60, 0.60, 0.50, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        32,
                        Color4(0.0, 0.0, 0.0, 0.4),
                        Color4(0.5, 0.5, 0.0, 0.6),
                        Color4(0.60, 0.60, 0.50, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        32);

// black rubber
Material cagd::MatRubberBlack = Material(
                        Color4(0.02, 0.02, 0.02, 0.4),
                        Color4(0.01, 0.01, 0.01, 0.6),
                        Color4(0.4, 0.4, 0.4, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        10,
                        Color4(0.02, 0.02, 0.02, 0.4),
                        Color4(0.01, 0.01, 0.01, 0.6),
                        Color4(0.4, 0.4, 0.4, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        10);

// cyan rubber
Material cagd::MatRubberCyan = Material(
                        Color4(0.0, 0.05, 0.05, 0.4),
                        Color4(0.4, 0.5, 0.5, 0.6),
                        Color4(0.04, 0.7, 0.7, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        10,
                        Color4(0.0, 0.05, 0.05, 0.4),
                        Color4(0.4, 0.5, 0.5, 0.6),
                        Color4(0.04, 0.7, 0.7, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        10);

// green rubber
Material cagd::MatRubberGreen = Material(
                        Color4(0.0, 0.05, 0.0, 0.4),
                        Color4(0.4, 0.5, 0.4, 0.6),
                        Color4(0.04, 0.7, 0.04, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        10,
                        Color4(0.0, 0.05, 0.0, 0.4),
                        Color4(0.4, 0.5, 0.4, 0.6),
                        Color4(0.04, 0.7, 0.04, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        10);

// red rubber
Material cagd::MatRubberRed = Material(
                        Color4(0.05, 0.0, 0.0, 0.4),
                        Color4(0.5, 0.4, 0.4, 0.6),
                        Color4(0.7, 0.04, 0.04, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        10,
                        Color4(0.05, 0.0, 0.0, 0.4),
                        Color4(0.5, 0.4, 0.4, 0.6),
                        Color4(0.7, 0.04, 0.04, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        10);

// white rubber
Material cagd::MatRubberWhite = Material(
                        Color4(0.05, 0.05, 0.05, 0.4),
                        Color4(0.5, 0.5, 0.5, 0.6),
                        Color4(0.7, 0.7, 0.7, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        10,
                        Color4(0.05, 0.05, 0.05, 0.4),
                        Color4(0.5, 0.5, 0.5, 0.6),
                        Color4(0.7, 0.7, 0.7, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        10);

// yellow rubber
Material cagd::MatRubberYellow = Material(
                        Color4(0.05, 0.05, 0.0, 0.4),
                        Color4(0.5, 0.5, 0.4, 0.6),
                        Color4(0.7, 0.7, 0.04, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        10,
                        Color4(0.05, 0.05, 0.0, 0.4),
                        Color4(0.5, 0.5, 0.4, 0.6),
                        Color4(0.7, 0.7, 0.04, 0.8),
                        Color4(0.000000, 0.000000, 0.000000, 0.0),
                        10);
