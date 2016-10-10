class CreateTests < ActiveRecord::Migration
  def change
    create_table :tests do |t|
      t.string :nombre
      t.string :apellido

      t.timestamps
    end
  end
end
