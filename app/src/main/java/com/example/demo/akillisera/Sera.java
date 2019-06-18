package com.example.demo.akillisera;

import com.google.firebase.database.IgnoreExtraProperties;

@IgnoreExtraProperties
public class Sera {

    public double anlikSicaklik;
    public double anlikNem;
    public double esikSicaklik;
    public double esikNem;
    public boolean cati;//True ise çalışıyor,değilse çalışmıyor
    public boolean fan;//True ise çalışıyor,değilse çalışmıyor
    public boolean suMotoru;//True ise çalışıyor değilse çalışmıyor
    public boolean havaDurumu;//True ise Açık değilse hava Yağışşlı
    public boolean toprakDurumu;//True ise Nemli ,değilse false
    public boolean uCati;
    public boolean uFan;
    public boolean uSuMotoru;

    public Sera() {
    }

    public Sera(double esikSicaklik,double esikNem,double anlikSicaklik, double anlikNem, boolean cati, boolean fan, boolean suMotoru,boolean havaDurumu
            ,boolean toprakDurumu,boolean uCati,boolean uFan,boolean uSuMotoru) {
        this.anlikSicaklik = anlikSicaklik;
        this.anlikNem = anlikNem;
        this.esikSicaklik = esikSicaklik;
        this.esikNem = esikNem;
        this.cati = cati;
        this.fan = fan;
        this.suMotoru = suMotoru;
        this.havaDurumu = havaDurumu;
        this.toprakDurumu = toprakDurumu;
        this.uCati = uCati;
        this.uFan = uFan;
        this.uSuMotoru = uSuMotoru;
    }
}
