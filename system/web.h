const char webpage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>ABCD Chocolate</title>
    <script>
        var av1,av2,av3;
        window.onload = function() {
            updateTotal();
            getChocolateCounts();
        }
        function getChocolateCounts() {
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/getCounts", true);
            xhr.onreadystatechange = function() {
                if (xhr.readyState === 4 && xhr.status === 200) {
                    var counts = JSON.parse(xhr.responseText);
                    document.getElementById('av1').innerHTML = counts.av1;
                    av1=counts.av1;
                    document.getElementById('av2').innerHTML = counts.av2;
                    av2=counts.av2;
                    document.getElementById('av3').innerHTML = counts.av3;
                    av3=counts.av3;
                }
            }
            xhr.send();
        }

        function incrementQuantity(id) {
            var quantity = parseInt(document.getElementById(id).innerHTML);
            if (quantity >= 10  ) {
                alert("You cannot add more than 10 chocolates.");
                if(quantity>=av1 || quantity>=av2 ||quantity>=av3 ){
                    alert("You cannot add insufficient chocolates.");
                }
            } else {
                document.getElementById(id).innerHTML = quantity + 1;
                updateTotal();
            }
        }

        function decrementQuantity(id) {
            var quantity = parseInt(document.getElementById(id).innerHTML);
            if (quantity > 0) {
                document.getElementById(id).innerHTML = quantity - 1;
                updateTotal();
            }
        }
        function updateTotal() {
            var quantity1 = parseInt(document.getElementById('quantity1').innerHTML);
            var quantity2 = parseInt(document.getElementById('quantity2').innerHTML);
            var quantity3 = parseInt(document.getElementById('quantity3').innerHTML);
            var total = quantity1 * 5 + quantity2 * 4 + quantity3 * 6;
            document.getElementById("total-bill").innerHTML = total;
        }
        function go() {
            var quantity1 = parseInt(document.getElementById('quantity1').innerHTML);
            var quantity2 = parseInt(document.getElementById('quantity2').innerHTML);
            var quantity3 = parseInt(document.getElementById('quantity3').innerHTML);
            var xhr1 = new XMLHttpRequest();
            var xhr2 = new XMLHttpRequest();
            var xhr3 = new XMLHttpRequest();
            xhr1.open("GET", "/quantity1?val1=" + quantity1 , true);
            xhr1.send();
            setTimeout("", 3000)
            xhr2.open("GET", "/quantity2?val2=" + quantity2 , true);
            xhr2.send();
            setTimeout("", 3000)
            xhr3.open("GET", "/quantity3?val3=" + quantity3 , true);
            xhr3.send();

        }
    </script>

    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: bisque;
        }

        h2 {
            text-align: center;
            color: #9b4dca;
        }

        .chocolates {
            display: flex;
            justify-content: center;
            align-items: center;
            margin-top: 30px;
        }

        .chocolate-item {
            margin: 20px;
            padding: 20px;
            background-color: #fff;
            box-shadow: 0 3px 6px rgba(0, 0, 0, 0.16);
            border-radius: 8px;
            text-align: center;
        }

        .chocolate-item img {
            width: 200px;
            height: 200px;
            object-fit: cover;
            border-radius: 8px;
            margin-bottom: 10px;
        }

        .chocolate-item h3 {
            font-size: 24px;
            color: #4c4c4c;
            margin-bottom: 10px;
        }

        .chocolate-item p {
            font-size: 18px;
            color: #9b4dca;
            margin-bottom: 10px;
        }


        .chocolate-item button {
            padding: 8px 12px;
            font-size: 18px;
            color: #fff;
            background-color: #9b4dca;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            margin: 5px;
        }


        .chocolate-item button:hover {
            background-color: #8046a0;
        }
        #total-bill {
            color: #9b4dca;
            font-size: 24px;
            font-weight: bold;
            text-align: right; /* align to the right */
            margin-right: 20px; /* add some margin */
            margin-bottom: 0; /* remove the default bottom margin */
        }

        .total-bill {
            padding: 8px 12px;
            color: #9b4dca;
            font-size: 24px;
            font-weight: bold;
            text-align: right; /* align to the right */
            margin: 50px; /* add some margin */
            float: right; /* align to the right */
        }

        .btn{
            padding: 8px 12px;
            font-size: 18px;
            color: #fff;
            background-color: #9b4dca;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            margin: 10px;
            float: right; /* align to the right */
            clear: both; /* clear the floats */
        }
    </style>
</head>
<body>
<h2>Our Chocolates</h2>
<div class="chocolates">
    <div class="chocolate-item">
        <img src="https://backend.lassana.com/images//products/CBL0119--1656676982.jpg" alt="Revello Cashew Chocolate">
        <h3>Revello Chocolate</h3>
        <p>Price: $5</p>
        <p class="have">Quantity we have: <span id="av1">0</span></p>
        <p>Quantity you need:<span id="quantity1">0</span></p>
        <button onclick="incrementQuantity('quantity3')">+</button>
        <button onclick="decrementQuantity('quantity3')">-</button>

    </div>
    <div class="chocolate-item">
        <img src="https://familyneeds.co.in/cdn/shop/products/1_73ea6786-bfbe-46fc-8fef-557713f3f3ff_600x600.jpg?v=1598633384" alt="Center Fresh Chewing Gum">
        <h3>Center Fresh Chewing Gum</h3>
        <p>Price: $4</p>
        <p class="have">Quantity we have: <span id="av2">0</span></p>
        <p>Quantity you need: <span id="quantity2">0</span></p>
        <button onclick="incrementQuantity('quantity2')">+</button>
        <button onclick="decrementQuantity('quantity2')">-</button>
    </div>
    <div class="chocolate-item">
        <img src="https://z.nooncdn.com/products/tr:n-t_400/v1532411041/N15224071A_1.jpg" alt="POLO">
        <h3>Polo</h3>
        <p>Price: $6</p>
        <p class="have">Quantity we have: <span id="av3">0</span></p>
        <p>Quantity you need:<span id="quantity3">0</span></p>
        <button onclick="incrementQuantity('quantity1')">+</button>
        <button onclick="decrementQuantity('quantity1')">-</button>
    </div>
</div>

<div class="total-bill">Total Bill: $<span id="total-bill">0</span></div>
<button class="btn" onclick="go()">Let's go</button>


</body>
</html>
)rawliteral";
