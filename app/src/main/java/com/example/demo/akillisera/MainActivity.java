package com.example.demo.akillisera;

import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;


public class MainActivity extends AppCompatActivity {


    FirebaseDatabase database,mDatabase;

    DatabaseReference myRef;

    TextView anlikSicaklik,anlikNem,esikDegerSicaklik,esikDegerNem,suMotoruDurumu,fanDurumu,catiDurumu,havaDurumu,toprakDurumu,txtBilgi;

    Button esikSicaklikArttir,esikNemArttir,esikSicaklikAzalt,esikNemAzalt,btnSuMotoruAc,btnSuMotoruKapat
            ,btnFanAc,btnFanKapa,btnCatiAc,btnCatiKapat;

    Sera sera;
    String suMotoru,fan,cati;



    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        database = FirebaseDatabase.getInstance();
        //database.setPersistenceEnabled(true);
        mDatabase = database.getInstance();
        myRef = mDatabase.getReference();
        myRef.keepSynced(true);
        initViews();
        init();
        butonDinleyiciler();

    }



    private void initViews() {

        anlikSicaklik = (TextView) findViewById(R.id.txtAnlikSicaklik);
        anlikNem = (TextView) findViewById(R.id.anlikNem);
        suMotoruDurumu = (TextView) findViewById(R.id.txtSuMotoruAnlik);
        fanDurumu = (TextView) findViewById(R.id.fanDurumu);
        catiDurumu = (TextView) findViewById(R.id.catiDurumu);
        esikDegerSicaklik = (TextView) findViewById(R.id.esikDegerSicaklik);
        esikDegerNem = (TextView) findViewById(R.id.esikDegerNem);
        havaDurumu = (TextView) findViewById(R.id.txtHavaDurumu);
        toprakDurumu = (TextView) findViewById(R.id.txtToprakDurumu);
        txtBilgi = (TextView) findViewById(R.id.txtBilgi);


        esikSicaklikArttir = (Button) findViewById(R.id.btnSicaklikArttir);
        esikNemArttir = (Button) findViewById(R.id.btnNemArttir);
        esikSicaklikAzalt = (Button) findViewById(R.id.btnSicaklikAzalt);
        esikNemAzalt = (Button) findViewById(R.id.btnNemAzalt);

        btnSuMotoruAc = (Button) findViewById(R.id.btnSuMotoruAc);
        btnSuMotoruKapat = (Button) findViewById(R.id.btnSuMotoruKapat);
        btnFanAc = (Button) findViewById(R.id.btnFanAc);
        btnFanKapa = (Button) findViewById(R.id.btnFanKapa);
        btnCatiAc = (Button) findViewById(R.id.btnCatiAc);
        btnCatiKapat = (Button) findViewById(R.id.btnCatiKapat);

    }


    private void init(){




        myRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                // This method is called once with the initial value and again
                // whenever data at this location is updated.
                Sera gelenSera = dataSnapshot.getValue(Sera.class);
                sera = gelenSera;
                anlikSicaklik.setText(""+sera.anlikSicaklik);
                esikDegerSicaklik.setText(""+sera.esikSicaklik);
                esikDegerNem.setText(""+sera.esikNem);
                anlikNem.setText(""+sera.anlikNem);
                havaDurumu.setText(""+sera.havaDurumu);
                toprakDurumu.setText(""+sera.toprakDurumu);


                if (sera.toprakDurumu)
                {
                    toprakDurumu.setText("Nemli");
                    btnSuMotoruAc.setClickable(false);
                    btnSuMotoruAc.setBackgroundResource(R.drawable.button_non_clickable);
                    btnSuMotoruKapat.setClickable(false);
                    btnSuMotoruKapat.setBackgroundResource(R.drawable.button_non_clickable);

                }

                else
                {
                    toprakDurumu.setText("Kuru");
                    btnSuMotoruAc.setClickable(true);
                    btnSuMotoruAc.setBackgroundResource(R.drawable.buttonshape);
                    btnSuMotoruKapat.setClickable(true);
                    btnSuMotoruKapat.setBackgroundResource(R.drawable.buttonshape2);

                }


                if (sera.havaDurumu)
                {
                    havaDurumu.setText("Açık");
                    btnCatiAc.setClickable(true);
                    btnCatiAc.setBackgroundResource(R.drawable.buttonshape);
                    btnCatiKapat.setClickable(true);
                    btnCatiKapat.setBackgroundResource(R.drawable.buttonshape2);
                }

                else
                {
                    havaDurumu.setText("Yağışlı");
                    btnCatiAc.setClickable(false);
                    btnCatiAc.setBackgroundResource(R.drawable.button_non_clickable);
                    btnCatiKapat.setClickable(false);
                    btnCatiKapat.setBackgroundResource(R.drawable.button_non_clickable);
                    sera.uCati=false;
                    myRef.setValue(sera);
                }


                if (sera.suMotoru){
                    suMotoruDurumu.setText("Açık");
                }
                else
                {
                    suMotoruDurumu.setText("Kapalı");
                }

                if (sera.fan){
                    fanDurumu.setText("Açık");
                }
                else
                {
                    fanDurumu.setText("Kapalı");
                }

                if (sera.cati){
                    catiDurumu.setText("Açık");
                }
                else
                {
                    catiDurumu.setText("Kapalı");
                }

                if(sera.uFan)
                {
                    fan = "Fan";
                }
                else
                {
                    fan="";
                }

                if(sera.uCati)
                {
                    cati = "Çatı";
                }

                else
                {
                    cati="";
                }

                if(sera.uSuMotoru)
                {
                    suMotoru = "Su Motoru";
                }
                else
                {
                    suMotoru = "";
                }

                if (cati.equals("") && fan.equals("") && suMotoru.equals(""))
                    txtBilgi.setText("");
                else
                txtBilgi.setText(fan+" "+cati+" "+suMotoru+" kullanıcı taraflı açık durumda");

                if(sera.esikNem < sera.anlikNem || sera.esikSicaklik < sera.anlikSicaklik)
                {
                    btnFanAc.setClickable(false);
                    btnFanAc.setBackgroundResource(R.drawable.button_non_clickable);
                    btnFanKapa.setClickable(false);
                    btnFanKapa.setBackgroundResource(R.drawable.button_non_clickable);
                }
                else
                {
                    btnFanAc.setClickable(true);
                    btnFanAc.setBackgroundResource(R.drawable.buttonshape);
                    btnFanKapa.setClickable(true);
                    btnFanKapa.setBackgroundResource(R.drawable.buttonshape2);
                }

            }

            @Override
            public void onCancelled(DatabaseError error) {
                // Failed to read value
                Log.w("FIREBASE", "Failed to read value.", error.toException());
            }
        });
    }


    private void butonDinleyiciler()
        {

            esikSicaklikArttir.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    sera.esikSicaklik=(sera.esikSicaklik + 1.0);

                    myRef.setValue(sera);

                }
            });


            esikSicaklikAzalt.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    sera.esikSicaklik=(sera.esikSicaklik - 1.0);

                    myRef.setValue(sera);

                }
            });


            esikNemArttir.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    sera.esikNem=(sera.esikNem + 1.0);

                    myRef.setValue(sera);

                }
            });

            esikNemAzalt.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    sera.esikNem=(sera.esikNem - 1.0);

                    myRef.setValue(sera);

                }
            });

            btnSuMotoruAc.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    sera.uSuMotoru=true;
                    myRef.setValue(sera);
                }
            });

            btnSuMotoruKapat.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    sera.uSuMotoru=false;
                    myRef.setValue(sera);
                }
            });

            btnFanAc.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    sera.uFan=true;
                    myRef.setValue(sera);
                }
            });

            btnFanKapa.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    sera.uFan=false;
                    myRef.setValue(sera);
                }
            });

            btnCatiAc.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    sera.uCati=true;
                    myRef.setValue(sera);
                }
            });

            btnCatiKapat.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    sera.uCati=false;
                    myRef.setValue(sera);
                }
            });


        }


}
