#pragma once

enum class CError
{
    sukces,
    brak_pliku,
    niepoprawny_plik,
    ujemny_argument,
    niedopasowany_parametr,  // input mismatch
    indeks_poza_zasiegiem,   // index out of bounds
    dereferencja_nullptr

};