#include "Configware.h"				//<! Contient la configuration globale du PIC : clock, GPIO
#include "odoLibre.h"
#include "Motors.h"
#include "Regulator.h"
#include "consigne.h"
#include "mouvements.h"
#include "GenerTraj.h"
#include "canFnc.h"
#include "../libdspic/timers.h"
#include "../libdspic/CanDspic.h"
#include <xc.h>
#include <math.h>


#define DBG_PIN0	(LATCbits.LATC5)            // pattes de debug pour mesurer des temps d'ex�cution
#define DBG_PIN1	(LATBbits.LATB5)


// variables ISR
volatile int isrRegFlag;                        //!< flag indiuant si le r�gulateur (et le g�n�rateur de consigne) sont actifs
volatile regType patinageFlag = NO_PATINAGE;

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void){
    IFS0bits.T1IF = 0;
    DBG_PIN1 = 1;
    // on envoie la position AVANT le calcul de l'odom�trie pour �tre certain qu'un PROP_SET_POSITION soit suivi par l'envoi de
    canSendPos(odoGetAbsPos());                   // la nouvelle position, ce qui sert d'acquittement � l'ordre. (on est en retard de 10ms, mais c'est pas grave))
    calculeOdometrie();                         // on calcule la position absolue mesur�e avec les encodeurs libres
    if (isrRegFlag) {
        csgCompute();                           // on calcule la nouvelle consigne
        patinageFlag = regCompute();            // on ex�cute le r�gulateur de position+vitesse
    }
    DBG_PIN1 = 0;
}



///////////////////////////////////////////////////////////////////////////////////////////////////
//	MAIN FUNCTION
///////////////////////////////////////////////////////////////////////////////////////////////////

int main(void) {
    propStateType state = DISABLED;         //!< Etat de la propulsion
    propStateType oldState = DISABLED;      //!< derni�re valeur de l'�tat envoy�e sur le CAN
    csgStatusType csgStatus;                //!< Statut du g�n�rateur de consigne : indique si le mouvement est en cours ou fini

    // Variables pour les commandes de mouevements relatifs
    translationParamType translationParam;  //!< contient les param�tres de la translation � effectuer
    rotationParamType rotationParam;        //!< contient les param�tres de la rotation � effectuer



    pllConfig();                // configure l'horloge de PIC
    TRISCbits.TRISC5 = 0;       // configure les pins de debug en sortie
    TRISBbits.TRISB5 = 0;

                // initialise les p�riph�riques QEI pour la mesure des encodeurs
                 // initialise les p�riph�riques PWM pour le contr�le des moteurs

    timerSetup(TIMER_1, 10);                    // Configuration du timer1 pour avoir une base de temps de 10ms
    _T1IE = 1;
    //timerInterrupt(TIMER_1, &propInterrupt);    // configuration de l'ISR
    timerStart(TIMER_1);
    DBG_PIN0 = 0;
    //TVD
    motorsInit();  
    motorsEnable();


    //translationParamType val = {100.0,100.0,100.0};
    //translationParam = val;
    motorsSetSpeed(1,1);
    //addTranslation(translationParam);    
    
    
    return (1);
}
