let current_id = undefined
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
    let id = parseInt(document.querySelector('.table_blur').lastElementChild.id)
    id = isNaN(id)? 0 : id + 1
    let ship = {
        'id' : id,
        'displacement' : parseFloat(document.getElementById('d_ship').value),
        'country' : document.getElementById('country-select').value.toString(),
        'name' : document.getElementById('n-input').value.toString(),
        'typeShip' : document.getElementById('tsh').value.toString()
    }
    fetch(`https://lab8-psp.firebaseio.com/ships/ship${id}.json`,{
        method: 'POST',
        body: JSON.stringify(ship)
    })
        .then(() => console.log("ship was successfully added"))
        .then(() => document.querySelector('.table_c').innerHTML = "")
        .then(() => showShips())
        .catch(error => console.log(error))
}

function __innerUpdate(id){
    let tr = document.getElementById(id)
    let country = tr.querySelector('.country').innerHTML
    let displacement = tr.querySelector('.displacement').innerHTML
    let id_ship = tr.querySelector('.id').innerHTML
    let name = tr.querySelector('.name').innerHTML
    let typeShip = tr.querySelector('.typeShip').innerHTML

    document.getElementById('d_ship').value = displacement
    document.getElementById('country-select').value = country
    document.getElementById('n-input').value = name
    document.getElementById('tsh').value = typeShip

    current_id = id_ship
}

/**
 *
 * @param id {number}
 */
function updateShip(){
    let ship = {
        'id' : current_id,
        'displacement' : parseFloat(document.getElementById('d_ship').value),
        'country' : document.getElementById('country-select').value.toString(),
        'name' : document.getElementById('n-input').value.toString(),
        'typeShip' : document.getElementById('tsh').value.toString()
    }
    fetch(`https://lab8-psp.firebaseio.com/ships/ship${current_id}.json`,{
        method: 'PUT',
        headers:{
            'Access-Control-Allow-Methods': 'GET,HEAD,POST'
        },
        body: JSON.stringify(ship)
    })
        .then(() => console.log("ship was successfully update"))
        .then(() => document.querySelector('.table_c').innerHTML = "")
        .then(() => showShips())
        .catch(error => console.log(error))
}

