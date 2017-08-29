#ifndef TEMPERATURECONVERTER_H
#define TEMPERATURECONVERTER_H

class TemperatureConverter
{
public:
    void setCelsius(float);

    void setFahrenheit(float);

    void setKelvin(float);

    float getCelsius();

    float getFahrenheit();

    float getKelvin();

private:
    float celsius;

    float fahrenheit;

    float kelvin;

    void computeFahrenheitFromCelsius();

    void computeCelsiusFromFahrenheit();

    void computeKelvinFromCelsius();

    void computeKelvinFromFahrenheit();

    void computeCelsiusFromKelvin();

    void computeFahrenheitFromKelvin();

};

#endif // TEMPERATURECONVERTER_H
