const nameHeader = ['COUNTRY', 'DISPLACEMENT', 'ID', 'NAME', 'TYPE_SHIP']

/**
 * Create needed element DOM-tree
 * @param element {string}
 * @returns {*}
 */
function generateElement(element){
    return document.createElement(element)
}

function generateHeader(){
    let tr = generateElement('tr')
    nameHeader.forEach((element, index) => {
        let th = generateElement('th')
        th.innerText = nameHeader[index]
        tr.appendChild(th)
    })

    let thRem = generateElement('th')
    thRem.innerText = "REMOVE"
    tr.appendChild(thRem)

    let thUpd = generateElement('th')
    thUpd.innerText = "UPDATE"
    tr.appendChild(thUpd)

    return tr
}
/**
 * Generate every row table with ships
 * @param object {{}}
 */
function generateRowTable(object){
    let tr = generateElement('tr')
    tr.id = object.id

    for (let properties in object){
        let th = generateElement('th')
        th.innerText = object[properties]
        th.className = properties
        tr.appendChild(th)
    }

    const btnRemove = generateElement('input')
    btnRemove.type = 'button'
    btnRemove.name = 'btn_remove'
    btnRemove.value = 'Remove'

    btnRemove.onclick = () => {
        removeShip(tr.id)
    }

    const btnUpdate = generateElement('input')
    btnUpdate.type = 'button'
    btnUpdate.name = 'btn_upd'
    btnUpdate.value = 'Update'
    btnUpdate.id = "open-button"
    btnUpdate.onclick = () => {
        updateShip(tr.id)
    }

    let thBtnRem = generateElement('th')
    thBtnRem.appendChild(btnRemove)
    tr.appendChild(thBtnRem)

    let thBtnUpdate = generateElement('th')
    thBtnUpdate.appendChild(btnUpdate)
    tr.appendChild(thBtnUpdate)

    return tr
}

/**
 * Generate table for UI
 * @param response {{}}
 */
function generateTable(response){
    const rootElement = document.querySelector('.table-с')

    let table = generateElement('table')
    table.className = 'table_blur'

    table.appendChild(generateHeader())

    for (const object in response){
        const tr = generateRowTable(response[object])
        table.appendChild(tr)
    }

    rootElement.appendChild(table)
}
