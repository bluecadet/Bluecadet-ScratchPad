# Bilinear Interpolation

This snippet provides a method for getting a point inside an irregular quadrilateral from normalized coordinates. This snippet was useful in converting blob tracking data from one coordinate system to another.


## Use Case:

//declare quad: points oriented clockwise from top left
vector<vec2> myQuad;
myQuad.push_back( vec2(   0,   0) );
myQuad.push_back( vec2( 100,   0) );
myQuad.push_back( vec2( 100, 100) );
myQuad.push_back( vec2(   0, 100) );

cout << mapNormToQuad( vec2( 0.5f, 0.5f), quad ) << endl;

Output:
> [  50, 50 ]