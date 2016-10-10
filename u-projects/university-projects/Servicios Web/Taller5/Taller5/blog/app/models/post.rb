class Post < ActiveRecord::Base
	has_many :comments
	validates :tittle, :body, presence: true, length: {minimum: 2}
end
