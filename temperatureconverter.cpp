#include "temperatureconverter.h"

void TemperatureConverter::setCelsius(float t)
{
    celsius = t;
    computeFahrenheitFromCelsius();
    computeKelvinFromCelsius();
}

float TemperatureConverter::getCelsius()
{
    return celsius;
}

void TemperatureConverter::setFahrenheit(float t)
{
    fahrenheit = t;
    computeCelsiusFromFahrenheit();
    computeKelvinFromFahrenheit();
}

float TemperatureConverter::getFahrenheit()
{
    return fahrenheit;
}

void TemperatureConverter::setKelvin(float t)
{
    kelvin = t;
    computeCelsiusFromKelvin();
    computeFahrenheitFromKelvin();
}

float TemperatureConverter::getKelvin()
{
    return kelvin;
}

void TemperatureConverter::computeFahrenheitFromCelsius()
{
    fahrenheit = 1.8*celsius + 32.0;
}

void TemperatureConverter::computeCelsiusFromFahrenheit()
{
    celsius = 5.0/9.0*(fahrenheit - 32.0);
}

void TemperatureConverter::computeKelvinFromCelsius()
{
    kelvin = celsius + 273.15;
}

void TemperatureConverter::computeKelvinFromFahrenheit()
{
    kelvin = (fahrenheit + 459.67)*5.0/9.0;
}

void TemperatureConverter::computeCelsiusFromKelvin()
{
    celsius = kelvin - 273.15;
}

void TemperatureConverter::computeFahrenheitFromKelvin()
{
    fahrenheit = (kelvin - 273.15)*9.0/5.0 + 32.0;
}
