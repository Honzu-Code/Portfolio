let button = document.querySelector("#add");
let generate = document.querySelector("#generate");




function new_field()
{
  let data_to_insert =
  "<div class='mb-3'> \
        <label class='form-label'>Description Post</label> \
        <input type='text' class='form-control' name='descriptionPost' > \
    </div>";
  $("#generate").append(data_to_insert);

}
