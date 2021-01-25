/*___            _      _    _       _____    _        _
|  _ \ _ __ ___ (_) ___| | _| |_ _  |_   _|__| |_ _ __(_)___
| |_) | '__/ _ \| |/ _ \ |/ / __(_)   | |/ _ \ __| '__| / __|
|  __/| | | (_) | |  __/   <| |_ _    | |  __/ |_| |  | \__ \
|_|   |_|  \___// |\___|_|\_\\__(_)   |_|\___|\__|_|  |_|___/
              |__/

(A) Spezifikationen
Wir wollen ein Tetrisspiel programmieren, welches folgende Eigenschaften erfüllt.

Neues Spiel starten x

Spielfeld anzeigen x

Spiel beenden:
	Highscore speichern X
	Menü anzeigen x

Figuren Visualisieren:
	Figuren farbig machen x
	Figuren Fallen x
	Randomizer für die Form x

Benutzerinteraktion
	Figuren drehen -> rotate(); X
	Figuren Steuern -> move(); X
	Möglichkeit, eine Figur zurückzustellen -> change(); X
	Spiel pausieren und Menü anzeigen -> pause(); X

Wenn eine Reihe voll ist:
	Punkte	-> addScore(); X
	Reihe löschen -> removeRow(); X

Wenn das Feld voll ist:
	Spiel beenden -> gameOver(); X

Menü:
	Art des Tetrisspiels wählen (originale "Bugs") X
	Spiel beenden X
	Zurück zum aktuellen Spiel X
	Highscore anzeigen X
*/


(B) Design

//Jede form wird in einem Array abgespeichert. Außerdem müssen Informationen, wie der Drehpunkt der Form gespeichert werden

Int Score; //Aktuelle Spielstand

Int Game[höhe][breite]; //Aktuelle Spielfeld

Int Current[höhe][breite]; // Position der aktuell fallenden Figur

Void startGame() {
	/*
		Game[][] wird auf den Anfangszustand zurückgesetzt.
		Score = 0;
	*/
}

void saveHighscore() {
	/*
		Der aktuelle Score wird in ein Textdokument im gleichen Ordner gespeichert
	*/
}

void endGame() {
	/*
		evtl. Speicher freigeben
		Programm beenden
	*/
}

resumeGame() {
	/*
		Zurück zum aktuellen Spiel
	*/
}

void showHighscore() {
	/*
		Der aktuelle Score wird angezeigt
	*/
}


void saveHighscore() {
	/*
		Der aktuelle Score wird in ein Textdokument im gleichen Ordner gespeichert
	*/
}


void showMenu(int gameStatus) {
	/*
		Art des Tetrisspiels wählen (originale "Bugs")
		Buttons für:
		endGame();
		startGame();
		if(gameStatus == 1) {
			resumeGame();
		}
		showHighscore();
	*/
}

showGame() {
	/*
		Game[][] und Current[][] werden interpretiert und angezeigt
	*/
}

playGame() {
	/*
		Alle Nutzereingaben werden eingelesen und entsprechend umgesetzt
		Entsprechend evtl. Aufruf von
			rotate();
			Move();
			Change();
			Pause();
		Danach in jedem Fall displayGame();
	*/
}

gameOver() {
	/*
		saveHighscore();
		showMenu();
	*/
}

void removeRow() {
	/*
		Wenn Reihe voll ist, dann soll diese gelöscht werden
		addScore();
	*/
}

void addScore() {
	/*
		Rechne Score drauf
	*/
}

rotate(int direction) {}

move(int direction){}

change(){}

pause(){
	showMenu(1);
}

main() {
	showMenu(0);
}
