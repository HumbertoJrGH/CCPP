#include <iostream>
#include <cmath>
#include <corecrt_math_defines.h>

class Geo
{
public:
	Geo(float latitude, float longitude) : lat(latitude), lon(longitude) {}
	float getLatitude() const { return lat; }
	float getLongitude() const { return lon; }
	float calcAngle(const Geo& geo) const {
		return calcRad(geo) * 180 / M_PI;
	}
	float calcRad(const Geo& geo) const {
		float deltaLat = lat - geo.lat;
		float deltaLon = lon - geo.lon;
		return atan2(deltaLat, deltaLon);		
	}

private:
	float lat;
	float lon;
};