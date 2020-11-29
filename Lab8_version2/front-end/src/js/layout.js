/**
 * show content table
 */
function showShips(){
    fetch("https://lab8-psp.firebaseio.com/ships.json")
        .then(response => response.json())
        .then(response => generateTable(response))
}

setTimeout(showShips, 0)

/**
 * Remove ship in firebase
 * @param id {int}
 */
function removeShip(id) {
    fetch(`https://lab8-psp.firebaseio.com/ships/ship${id}.json`, {
        method: 'DELETE'
        })
        .then(() => document.getElementById(    `${id}`).innerHTML = "")
        .then(() => console.log(`Delete ship with id = ${id} completed successfully`))
        .catch(err => console.log(err))
}

/**
 * Add ship in firebase
 *
 */
function addedShip(){

}

/**
 *
 * @param id {number}
 */
function updateShip(id){

}

let modal = document.querySelector("#modal"),
    modalOverlay = document.querySelector("#modal-overlay"),
    closeButton = document.querySelector("#close-button"),
    openButton = document.querySelector("#open-button");

closeButton.addEventListener("click", function() {
    modal.classList.toggle("closed");
    modalOverlay.classList.toggle("closed");
});

openButton.addEventListener("click", function() {
    modal.classList.toggle("closed");
    modalOverlay.classList.toggle("closed");
});

