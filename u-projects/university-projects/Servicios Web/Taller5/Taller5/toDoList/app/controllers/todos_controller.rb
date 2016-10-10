class TodosController < ApplicationController
  def index
  	@todo_items = Todo.all # Query para coger todos los todos
  	@new_todo = Todo.new
  end

  def add
  	todo = Todo.create(:todo_item => params[:todo][:todo_item])
  	todo.save
  	if todo.valid?
  		flash[:success] = "Todo added successfully" 
  	else
  		flash[:error] = todo.errors.full_messages.join("<br>").html_safe
  	end
  	redirect_to index_path	
  end
end
